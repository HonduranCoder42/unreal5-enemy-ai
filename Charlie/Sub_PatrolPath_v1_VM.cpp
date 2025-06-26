// Fill out your copyright notice in the Description page of Project Settings.

/*
 * @file Sub_PatrolPath_v1_VM.cpp
 *
 * @brief Provides code to properly pull information about the patrol path object.
 *
 *  This file includes functions for properly getting necessary information about
 *  a patrol path object in order to properly navigate through it. These functions
 *  include getting a specific patrol point from an index of points and the total
 *  number of patrol points in a full patrol point array.
 *
 *  @author Victor Mondragon
 *  @date 2025-02-04
 **/

#include "Sub_PatrolPath_v1_VM.h"

// Sets default values
ASub_PatrolPath_v1_VM::ASub_PatrolPath_v1_VM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector ASub_PatrolPath_v1_VM::GetPatrolPoint(int const index) const
{
	return PatrolPoints[index];
}

int ASub_PatrolPath_v1_VM::Num() const
{
	return PatrolPoints.Num();
}