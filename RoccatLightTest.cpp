#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "ROCCAT_Talk.h"

int currentColors[3] = { 0, 0, 0 };
int objectiveColors [3] = { 25500, 0, 0 };
bool haveMetObjecive[3] = { false, false, false };
bool allObjectivesMet = false;

int speed;

void changeObjective()
{
	int currentObjectiveColors[3] = { objectiveColors[0], objectiveColors[1], objectiveColors[2] };

	if (currentObjectiveColors[0] == 25500 && currentObjectiveColors[1] == 0 && currentObjectiveColors[2] == 0)
	{
		objectiveColors[0] = 25500;
		objectiveColors[1] = 25500;
		objectiveColors[2] = 0;
	}
	if (currentObjectiveColors[0] == 25500 && currentObjectiveColors[1] == 25500 && currentObjectiveColors[2] == 0)
	{
		objectiveColors[0] = 0;
		objectiveColors[1] = 25500;
		objectiveColors[2] = 0;
	}
	if (currentObjectiveColors[0] == 0 && currentObjectiveColors[1] == 25500 && currentObjectiveColors[2] == 0)
	{
		objectiveColors[0] = 0;
		objectiveColors[1] = 25500;
		objectiveColors[2] = 25500;
	}
	if (currentObjectiveColors[0] == 0 && currentObjectiveColors[1] == 25500 && currentObjectiveColors[2] == 25500)
	{
		objectiveColors[0] = 0;
		objectiveColors[1] = 0;
		objectiveColors[2] = 25500;
	}
	if (currentObjectiveColors[0] == 0 && currentObjectiveColors[1] == 0 && currentObjectiveColors[2] == 25500)
	{
		objectiveColors[0] = 25500;
		objectiveColors[1] = 0;
		objectiveColors[2] = 25500;
	}
	if (currentObjectiveColors[0] == 25500 && currentObjectiveColors[1] == 0 && currentObjectiveColors[2] == 25500)
	{
		objectiveColors[0] = 25500;
		objectiveColors[1] = 0;
		objectiveColors[2] = 0;
	}
}

int main() {
	CROCCAT_Talk roccat;

	if (roccat.init_ryos_talk()) {
		roccat.set_ryos_kb_SDKmode(TRUE);

		std::cout << "Color flow speed (bpm): ";
		std::cin >> speed;

		speed = 25500 / (((1.0 / (speed / 60.0)) * 100.0) / 2.0);

		while (true) {
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				break;
			}

			if (allObjectivesMet == false) {
				for (int i = 0; i < 3; i++)
				{
					if (currentColors[i] <= objectiveColors[i])
					{
						currentColors[i] += speed;
						if (currentColors[i] >= objectiveColors[i])
						{
							currentColors[i] = objectiveColors[i];
							haveMetObjecive[i] = true;
						}
					}
				}

				allObjectivesMet = true;

				for (int i = 0; i < 3; i++)
				{
					if (haveMetObjecive[i] == false)
					{
						allObjectivesMet = false;
					}
				}
			}


			if (allObjectivesMet == true) 
			{
				for (int i = 0; i < 3; i++)
				{
					if (currentColors[i] >= 0)
					{
						currentColors[i] -= speed;
						if (currentColors[i] <= 0)
						{
							currentColors[i] = 0;
							haveMetObjecive[i] = false;
						}
					}
				}

				allObjectivesMet = false;

				for (int i = 0; i < 3; i++)
				{
					if (haveMetObjecive[i] == true)
					{
						allObjectivesMet = true;
					}
				}

				if (allObjectivesMet == false) 
				{
					changeObjective();
				}
			}

			//std::cout << currentColors[0] << ' ' << currentColors[1] << ' ' << currentColors[2] << '\n';
			roccat.Set_LED_RGB(0x01, 0x01, 0x01, currentColors[0]/100, currentColors[1] /100, currentColors[2] /100);
			Sleep(10);
		}

		roccat.RestoreLEDRGB();

		roccat.set_ryos_kb_SDKmode(FALSE);
	}
}