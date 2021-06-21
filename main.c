#include "include/raylib.h"

#define WIDTH 600
#define HEIGHT 600
#define RESOLUTION 5

Color deadColor = { 87, 16, 39, 255 };
Color liveColor = { 116, 234, 230, 255 };
Color background = { 14, 19, 44, 255 };

typedef struct {
	int value;
	Color color;
} Cel;

int rows = HEIGHT / RESOLUTION, cols = WIDTH / RESOLUTION;
int state = 0;
int colorized = 1;

void updateGrid(Cel grid[rows][cols], Cel calc[rows][cols], float time);
void updateGridColor(Cel grid[rows][cols], Cel calc[rows][cols], float time);
void copyGrid(Cel grid[rows][cols], Cel calc[rows][cols]);
int countNeighbors(int x, int y, Cel grid[rows][cols]);
float lerp(float init, float end, float amount);
Color colorLerp(Color init, Color end, float amount);
void randomGrid(Cel grid[rows][cols], Cel calc[rows][cols]);
void clearGrid(Cel grid[rows][cols], Cel calc[rows][cols]);

int main() {
	InitWindow(WIDTH, HEIGHT, "Game of Life");
	SetTargetFPS(30);

	Cel grid[rows][cols];
	Cel gridCalc[rows][cols];

	for (int i = 1; i < rows - 1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {
			int rule = i % 2 == 0 && j % 2 == 0 || j < i && i % 2 == 0;

			grid[i][j].value = rule == 0 ? -1 : 1;
			if (grid[i][j].value == 1) {
				grid[i][j].color = liveColor;
			} else {
				grid[i][j].color = background;
			}

			gridCalc[i][j].value = grid[i][j].value;
			gridCalc[i][j].color = grid[i][j].color;
		}
	}

	while (!WindowShouldClose()) {

		float delta = GetFrameTime();

		if (state) {
			if (colorized) updateGridColor(grid, gridCalc, delta);
			else updateGrid(grid, gridCalc, delta);
		}

		if (IsKeyPressed(KEY_SPACE)) {
			state = !state;
		}

		if (IsKeyPressed(KEY_R)) {
			state = 0;
			randomGrid(grid, gridCalc);
		}

		if (IsKeyPressed(KEY_N)) {
			state = 0;
			clearGrid(grid, gridCalc);
		}

		if (IsKeyPressed(KEY_C)) {
			colorized = !colorized;
		}

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !state) {
			int x = (int) GetMouseX() / RESOLUTION, y = (int) GetMouseY() / RESOLUTION;
			gridCalc[x][y].value = 1;
			gridCalc[x][y].color = liveColor;
		} else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && !state) {
			int x = (int) GetMouseX() / RESOLUTION, y = (int) GetMouseY() / RESOLUTION;
			gridCalc[x][y].value = -1;
			gridCalc[x][y].color = BLACK;
		}

		BeginDrawing();

		ClearBackground(background);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (colorized) {
					DrawRectangle(i * RESOLUTION, j * RESOLUTION, RESOLUTION, RESOLUTION, gridCalc[i][j].color);
				} else {
					if (gridCalc[i][j].value == 1) DrawRectangle(i * RESOLUTION, j * RESOLUTION, RESOLUTION, RESOLUTION, WHITE);
				}
			}
		}

		if (!state) {
			DrawText("Paused", 10, 10, 32, RED);
		}

		EndDrawing();

		copyGrid(grid, gridCalc);
	}

	CloseWindow();

	return 0;
}

void clearGrid(Cel grid[rows][cols], Cel calc[rows][cols]) {
	for (int i = 1; i < rows - 1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {

			grid[i][j].value = -1;
			grid[i][j].color = background;

			calc[i][j].value = grid[i][j].value;
			calc[i][j].color = grid[i][j].color;
		}
	}
}

void randomGrid(Cel grid[rows][cols], Cel calc[rows][cols]) {
	for (int i = 1; i < rows - 1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {

			grid[i][j].value = GetRandomValue(0, 1) == 0 ? -1 : 1;
			if (grid[i][j].value == 1) {
				grid[i][j].color = liveColor;
			} else {
				grid[i][j].color = background;
			}

			calc[i][j].value = grid[i][j].value;
			calc[i][j].color = grid[i][j].color;
		}
	}
}

void updateGridColor(Cel grid[rows][cols], Cel calc[rows][cols], float time) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {

			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
				calc[i][j].value = -1;
			} else {
				int sum = countNeighbors(i, j, grid);
				Cel cel = grid[i][j];

				if (cel.value == 1 && (sum < 2 || sum > 3)) {
					calc[i][j].value = 0;
				} else if ((cel.value == 0 || cel.value == -1) && sum == 3) {
					calc[i][j].value = 1;
				} else {
					calc[i][j].value = cel.value;
					calc[i][j].color = cel.color;
				}
			}

			if (calc[i][j].value == 0) {
				if (calc[i][j].color.r <= deadColor.r && calc[i][j].color.g <= deadColor.g && calc[i][j].color.b <= deadColor.b) {
					calc[i][j].color = colorLerp(calc[i][j].color, background, time / 2);
				} else {
					calc[i][j].color = colorLerp(calc[i][j].color, deadColor, time * 2);
				}
			} else if (calc[i][j].value == 1) {
				calc[i][j].color = liveColor;
			} else {
				calc[i][j].color = background;
			}
		}
	}
}

void updateGrid(Cel grid[rows][cols], Cel calc[rows][cols], float time) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {

			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
				calc[i][j].value = -1;
			} else {
				int sum = countNeighbors(i, j, grid);
				Cel cel = grid[i][j];

				if (cel.value == 1 && (sum < 2 || sum > 3)) {
					calc[i][j].value = 0;
				} else if ((cel.value == 0 || cel.value == -1) && sum == 3) {
					calc[i][j].value = 1;
				} else {
					calc[i][j].value = cel.value;
				}
			}
		}
	}
}

void copyGrid(Cel grid[rows][cols], Cel calc[rows][cols]) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			grid[i][j].value = calc[i][j].value;
			grid[i][j].color = calc[i][j].color;
		}
	}
}

int countNeighbors(int x, int y, Cel grid[rows][cols]) {
	int sum = 0;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			int neighborValue = grid[x + i][y + j].value;
			sum += neighborValue == -1 ? 0 : neighborValue;
		}
	}

	sum -= grid[x][y].value == -1 ? 0 : grid[x][y].value;

	return sum;
}

float lerp(float init, float end, float amount) {
	return init + amount * (end - init);
}

Color colorLerp(Color init, Color end, float amount) {
	Color newColor = { lerp(init.r, end.r, amount), lerp(init.g, end.g, amount), lerp(init.b, end.b, amount), 255 };
	return newColor;
}