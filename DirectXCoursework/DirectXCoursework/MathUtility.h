#pragma once
float lerp(float start,float end, float delta)
{
	return start * (1.0 - delta) + end * (delta);
}