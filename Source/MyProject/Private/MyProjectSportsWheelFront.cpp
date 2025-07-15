#include "MyProjectSportsWheelFront.h"

UMyProjectSportsWheelFront::UMyProjectSportsWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;

	WheelRadius = 40.f;
	WheelWidth = 60.0f;

	FrictionForceMultiplier = 3.5f;

	SlipThreshold = 50.0f;
	SkidThreshold = 100.0f;
}