#pragma once
class UserInterface
{
public:
	UserInterface(int *SWH, int *HPBBH): SteeringWheelHandle(SWH),
		HPBarBaseHandle(HPBBH) {}
	~UserInterface();

	void Show(double Radian);
	void Inif();

private:
	const int *SteeringWheelHandle;
	const int *HPBarBaseHandle;
	int SWL, SWW;
};

