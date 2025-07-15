// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectOffroadWheelRear.h"

UMyProjectOffroadWheelRear::UMyProjectOffroadWheelRear()
{
	WheelRadius = 75.f;
	CorneringStiffness = 450.0f;
	FrictionForceMultiplier = 2.0f;
	
	SuspensionMaxRaise = 15.0f;
	SuspensionMaxDrop = 15.0f;
	WheelLoadRatio = 0.8f;
	SpringRate = 300.0f;
	SpringPreload = 100.0f;
	SweepShape = ESweepShape::Shapecast;

	MaxBrakeTorque = 3000.0f;
	MaxHandBrakeTorque = 6000.0f;
}