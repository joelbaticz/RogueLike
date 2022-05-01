#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(int maxFrame, float animationLengthInSeconds)
{
	this->maxFrame = maxFrame;
	this->animationLengthInMiliSeconds = animationLengthInSeconds * 1000;
	currentFrame = 0;
	animationState = 0.0f;
}

AnimationPlayer::~AnimationPlayer() = default;

int AnimationPlayer::GetMaxFrame()
{
	return maxFrame;
}

void AnimationPlayer::SetMaxFrame(int maxFrame)
{
	this->maxFrame = maxFrame;
}

void AnimationPlayer::SetAnimationLength(float animationLength)
{
	this->animationLengthInMiliSeconds = animationLength * 1000;
}

void AnimationPlayer::ResetAnimation()
{
	animationState = 0;
}


int AnimationPlayer::GetCurrentFrame(float fElapsedTime)
{
	animationState += fElapsedTime;

	// Correct animation state if overflown
	int overflowRate = (int)(animationState / animationLengthInMiliSeconds);
	animationState -= (float)(animationLengthInMiliSeconds * overflowRate);

	currentFrame = (int)((float)maxFrame * animationState / animationLengthInMiliSeconds);

	return currentFrame;
}
