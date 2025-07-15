#include "MyProjectSportsWheelFront.h"

UMyProjectSportsWheelFront::UMyProjectSportsWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;

	WheelRadius = 40.f;
	WheelWidth = 40.0f;

	FrictionForceMultiplier = 3.5f;

	SlipThreshold = 80.0f;
	SkidThreshold = 120.0f;
}