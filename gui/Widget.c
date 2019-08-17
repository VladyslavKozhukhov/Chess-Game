#include "Widget.h"


void destroyWidget(Widget* src) {
	if (src == NULL ) {
		return;
	}
	src->destroyWidget(src);
}
