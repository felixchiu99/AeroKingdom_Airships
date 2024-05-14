// Fill out your copyright notice in the Description page of Project Settings.


#include "ASIDamageable.h"

// Add default functionality here for any IASIDamageable functions that are not pure virtual.

void IASIDamageable::AddDamage(float fDamage)
{
}

void IASIDamageable::RemoveDamage(float fDamage)
{
}

float IASIDamageable::GetDurability()
{
	return 0.0f;
}

float IASIDamageable::GetMaxDurability()
{
	return 0.0f;
}

void IASIDamageable::OnDestroyed()
{
}

void IASIDamageable::OnDamage()
{
}

void IASIDamageable::OnFullDurability()
{
}

void IASIDamageable::OnRepair()
{
}
