#include "MyProjectSportsWheelRear.h"

UMyProjectSportsWheelRear::UMyProjectSportsWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByEngine = true;
	bAffectedByHandbrake = true;
	MaxSteerAngle = 0.0f;
	MaxHandBrakeTorque = 6000.0f;

	WheelRadius = 40.f;
	WheelWidth = 40.0f;

	FrictionForceMultiplier = 4.0f;

	SlipThreshold = 80.0f;
	SkidThreshold = 120.0f;
}