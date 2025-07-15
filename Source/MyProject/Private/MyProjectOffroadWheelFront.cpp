// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectOffroadWheelFront.h"

UMyProjectOffroadWheelFront::UMyProjectOffroadWheelFront()
{
	WheelRadius = 85.0f;
	CorneringStiffness = 450.0f;
	FrictionForceMultiplier = 2.0f;
	bAffectedByEngine = true;

	SuspensionMaxRaise = 20.0f;
	SuspensionMaxDrop = 20.0f;
	WheelLoadRatio = 1.0f;
	SpringRate = 250.0f;
	SpringPreload = 100.0f;
	SweepShape = ESweepShape::Shapecast;

	MaxBrakeTorque = 3000.0f;
	MaxHandBrakeTorque = 6000.0f;
}