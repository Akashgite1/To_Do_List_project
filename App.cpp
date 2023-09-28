#include"App.h"
#include"MAIN.h"

wxIMPLEMENT_APP(App);


bool App::OnInit()
{
	MAIN* main = new MAIN("To-Do List");
	main->SetClientSize(800, 600);
	main->Center();
	main->Show();

	return true;
}