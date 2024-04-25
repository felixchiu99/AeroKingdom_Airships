// Fill out your copyright notice in the Description page of Project Settings.


#include "ASAirship.h"
#include "AirshipController.h"
#include "Components/ArrowComponent.h"

AASAirship::AASAirship()
{
	PrimaryActorTick.bCanEverTick = true;
	Core->SetSimulatePhysics(true);
	Core->SetAngularDamping(SeperatedLinearDamping.Y);
	Core->SetCollisionProfileName(FName("Ship"));

	//Core->SetLinearDamping(0.2f);

	Balloon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BalloonMesh"));
	Balloon->SetupAttachment(Core);
	Balloon->SetCollisionProfileName(FName("Ship"));

	ShipBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	//ShipBase->SetRelativeScale3D(FVector(8.f, 8.f, 0.1f));
	ShipBase->SetupAttachment(Core);
	ShipBase->SetMassOverrideInKg("ShipBase", 10000.f, true);
	ShipBase->SetCollisionProfileName(FName("Ship"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/ Script / Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// check if path is valid. Check path of mesh in content browser.
	if (Base.Succeeded())
	{
		// mesh = valid path
		ShipBase->SetStaticMesh(Base.Object);	
		Balloon->SetStaticMesh(Base.Object);
		Balloon->SetRelativeLocation(FVector(0.f, 0.f, 1000.0f));
	}

	//create a cannon sub actor
	AirshipController = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("AirshipController"));
	AirshipController->SetChildActorClass(ACAttachmentType);
	AirshipController->SetupAttachment(ShipBase);
	AirshipController->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	
	RudderPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("RudderPoint"));
	RudderPoint->SetupAttachment(Balloon);
	RudderPoint->SetRelativeLocation(FVector(-1000.0f, 0.0f, 0.0f));

}

void AASAirship::BeginPlay()
{
	Super::BeginPlay();
	AAirshipController* ASControl = Cast<AAirshipController>(AirshipController->GetChildActor());
	ASControl->SetAirshipPointer(this);
	fHeight = GetActorLocation().Z;
}

void AASAirship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHeight();
	ApplyLift(DeltaTime);
	ApplyDamping(DeltaTime);
	ApplyYaw(DeltaTime);
	//DisplayAxisSpeed();
}

void AASAirship::MoveForward()
{
	ShipBase->AddForce(GetActorForwardVector() * PushStrength);
}

void AASAirship::MoveBackward()
{
	ShipBase->AddForce(GetActorForwardVector() * -PushStrength * 0.8f);
}

void AASAirship::AxisForward(float input)
{

}

void AASAirship::AxisUpward(float input)
{
	float LiftPower = (LiftLimit.Y - fCurrentHeight) / (LiftLimit.Y);
	LiftPower = FMath::Clamp(LiftPower * LiftPower, 0, 1);
	
	LiftPower *= input * fActiveLiftPower;

	if (fCurrentHeight < LiftLimit.X && LiftPower < 0) {
		LiftPower *= 0;
	}

	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Lift Power " + FString::SanitizeFloat(LiftPower)));

	Balloon->AddImpulse(FVector(0,0, LiftPower),"none",true);
	fHeight = GetActorLocation().Z;
}

void AASAirship::Yaw(float input)
{
	fRudderRotation += input * fRudderTurnSpeed * GetWorld()->GetDeltaSeconds();
	fRudderRotation = FMath::Clamp(fRudderRotation, RudderLimits.X, RudderLimits.Y);
	bRudderTurn = true;
}

void AASAirship::ApplyYaw(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(fRudderRotation));
	if (fRudderRotation > 0.5f || fRudderRotation < -0.5f) {
		float ForwardVelocity = FVector::DotProduct(GetVelocity(), GetActorForwardVector());
		float fRudder = fRudderRotation / ((abs(RudderLimits.X) + abs(RudderLimits.Y)) * 0.5f);
		Balloon->AddTorqueInDegrees(FVector(0, 0, fRudder * ForwardVelocity * fRudderTorqueMultiplier * DeltaTime), "None", true);
	}
	ReduceYaw(DeltaTime);
}

void AASAirship::ReduceYaw(float DeltaTime)
{
	if (!bRudderTurn) {
		if (fRudderRotation > 0.5f) 
		{
			fRudderRotation -= fRudderTurnSpeed * 0.7f * DeltaTime;
		}
		if (fRudderRotation < -0.5f)
		{
			fRudderRotation += fRudderTurnSpeed * 0.7f * DeltaTime;
		}
	}

	bRudderTurn = false;
}

void AASAirship::ApplyLift(float StepTime)
{
	ApplyNeutralLift(StepTime);
	ApplyReactiveLift(StepTime);
}

void AASAirship::ApplyNeutralLift(float StepTime, bool bDebug)
{
	Core->AddForceAtLocation(FVector(0, 0, 9.8f * 100 * Core->GetMass()), Balloon->GetComponentLocation());

	if (bDebug) {
		DrawDebugLine(GetWorld(), Balloon->GetComponentLocation(), Balloon->GetComponentLocation() + FVector(0, 0, 100.f), FColor::Red, false, 0.1f, ECC_WorldStatic, 1.f);
		DrawDebugLine(GetWorld(), Core->GetCenterOfMass(), Core->GetCenterOfMass() + FVector(0, 0, -100.f), FColor::Blue, false, 0.1f, ECC_WorldStatic, 1.f);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(Core->GetMass()));
	}
	
}

void AASAirship::ApplyReactiveLift(float StepTime, bool bDebug)
{
	if (fCurrentHeight < fHeight) {
		FVector linearVelocity = GetVelocity();
		Balloon->AddImpulse(FVector(0,0, abs(fHeight-GetActorLocation().Z) * fReactiveLiftMultiplier), "None", true);
	}
}

void AASAirship::UpdateHeight()
{
	fCurrentHeight = GetActorLocation().Z;
	if (fCurrentHeight < LiftLimit.X) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Height " + FString::SanitizeFloat(fCurrentHeight)));
	}
	if (fCurrentHeight > LiftLimit.Y) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Height " + FString::SanitizeFloat(fCurrentHeight)));
	}
}

void AASAirship::ApplyDamping(float DeltaTime)
{
	FVector linearVelocity = GetVelocity();
	float Speed = linearVelocity.Length();
	FVector CalculatedLinearDamping = SeperatedLinearDamping;
	float UpperSpeed = MaxSpeed;
	float UpperLimit = 0.0000023f * FMath::Pow(UpperSpeed, 3.7835f)+33.7812;

	CalculatedLinearDamping += FVector(Speed / UpperLimit);

	CalculatedLinearDamping.X = FMath::Clamp(CalculatedLinearDamping.X,0,1);
	CalculatedLinearDamping.Y = FMath::Clamp(CalculatedLinearDamping.Y,0,1);
	CalculatedLinearDamping.Z = FMath::Clamp(CalculatedLinearDamping.Z,0,1);

	FVector linearDampingTimesDeltaSeconds = CalculatedLinearDamping * DeltaTime;
	FVector Axis = FVector(0, 0, 0);

	Axis += ApplyAbsAxis(GetActorRotation().RotateVector(FVector(linearDampingTimesDeltaSeconds.X, 0, 0)));
	Axis += ApplyAbsAxis(GetActorRotation().RotateVector(FVector(0, linearDampingTimesDeltaSeconds.Y, 0)));
	Axis += FVector(0, 0, CalculatedLinearDamping.Z);


	FVector linearVelocityMultiplier = FVector(
		FGenericPlatformMath::Max(0, 1.0f - Axis.X),
		FGenericPlatformMath::Max(0, 1.0f - Axis.Y),
		FGenericPlatformMath::Max(0, 1.0f - Axis.Z));

	linearVelocity *= linearVelocityMultiplier;
	
	Core->SetAllPhysicsLinearVelocity(linearVelocity);
}

void AASAirship::DisplayAxisSpeed()
{
	FVector linearVelocity = GetVelocity();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("X-Speed " + FString::SanitizeFloat(FVector::DotProduct(linearVelocity, GetActorForwardVector()))));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Y-Speed " + FString::SanitizeFloat(FVector::DotProduct(linearVelocity, GetActorRightVector()))));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Z-Speed " + FString::SanitizeFloat(FVector::DotProduct(linearVelocity, GetActorUpVector()))));
	
}	

FVector AASAirship::ApplyAbsAxis(FVector Axis)
{
	return FVector(abs(Axis.X), abs(Axis.Y), abs(Axis.Z));
}


