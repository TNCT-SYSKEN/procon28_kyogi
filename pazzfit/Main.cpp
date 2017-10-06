#include "common.h"
#include "Control.h"

void Main() {
	Control control;

	const Font font(30);
	Graphics::SetBackground(Palette::White);

	while (System::Update()) {
		control.exe();
	}
}