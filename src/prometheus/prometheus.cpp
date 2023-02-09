#include "prometheus.h"
#include "text.h"

Prometheus::Prometheus() : Scene("prometheus")
{
	create_window("Prometheus", 100, 100, 640, 480, false);
	Text *beg_text = new Text("beginning_text");
	beg_text->set_text_boundaries("In the beginning there was but one man", 500);
	beg_text->set_position({-180, -220});

	Text *continue_text = new Text("continue_text");
	continue_text->set_text_boundaries("Press space to continue", 500);
	continue_text->set_position({-100, 80});

	add_game_object(beg_text);
	add_game_object(continue_text);
}
