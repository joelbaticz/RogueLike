#pragma once

class AnimationPlayer
{
private:
	int maxFrame;
	float animationLengthInMiliSeconds;
	int currentFrame;
	float animationState;
public:
	AnimationPlayer(int maxFrame, float animationLength);
	~AnimationPlayer();

	int GetMaxFrame();
	void SetMaxFrame(int maxFrame);
	void SetAnimationLength(float animationLength);
	void ResetAnimation();
	int GetCurrentFrame(float fElapsedTime);
};
