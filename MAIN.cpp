
#include "MAIN.h"
#include<wx/wx.h>
#include<vector>
#include<string>
#include "Task.h"


MAIN::MAIN(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventHandlers();
	AddSavedTasks();

}

void MAIN::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainfont(wxFontInfo(wxSize(0, 24)));

	panel = new wxPanel(this);
	panel->SetFont(mainfont);

	// head name To-Do-List 
	headtext = new wxStaticText(panel, wxID_ANY, "To-Do-List", wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headtext->SetFont(headlineFont);
	//  headtext-> SetBackgroundColour(*wxRED); we can set beckground colour 

	// input field geting input form user
	inputfield = new wxTextCtrl(panel, wxID_ANY, " ", wxPoint(100, 80), wxSize(495, 35), wxTE_PROCESS_ENTER);
	// after geting the input form user add it to the list
	addbutton = new wxButton(panel, wxID_ANY, "Add", wxPoint(600, 80), wxSize(100, 35));
	// store the input 
	checklist = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
	// delete all stored inputs 
	clearbutton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 525), wxSize(100, 35));


}

void MAIN::BindEventHandlers()
{
	addbutton->Bind(wxEVT_BUTTON, &MAIN::OnAddButtonClicked, this);
	inputfield->Bind(wxEVT_TEXT_ENTER, &MAIN::OnInputEnter, this);
	checklist->Bind(wxEVT_KEY_DOWN, &MAIN::Onlistkeydown, this);
	clearbutton->Bind(wxEVT_BUTTON, &MAIN::OnClearButtonClicked, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MAIN::OnWindowsClosed, this);
}

// showing previous saved tasks when we Again open app
void MAIN::AddSavedTasks()
{
	std::vector<Task> tasks = LoadTaskFromFile("tasks.txt");

	for (const Task& task : tasks) {
		int index = checklist->GetCount();
		checklist->Insert(task.description, index);
		checklist->Check(index, task.done);
	}
}

// add user input in Tasklist when we click Add button in App
void MAIN::OnAddButtonClicked(wxCommandEvent& evt)
{
	AddTaskFormInput();
}

// clear button function
void MAIN::OnClearButtonClicked(wxCommandEvent& evt)
{
	if (checklist->IsEnabled()) {
		return;
	}

	wxMessageDialog dialog(this, "Are you sure you want to close All Tasks?", "Clear", 
		wxYES_NO | wxCANCEL);
	int result = dialog.ShowModal();

	if (result == wxID_YES) {

		checklist->Clear();

	}
}

void MAIN::AddTaskFormInput()
{
	wxString description = inputfield->GetValue();

	if (!description.IsEmpty()) {
		checklist->Insert(description, checklist->GetCount());
		// clearing the input filed after adding task in list using add button 
		inputfield->Clear();
	}
	inputfield->SetFocus();
}

// add user input in Tasklist when we click enter form keyboard
void MAIN::OnInputEnter(wxCommandEvent& evt)
{
	AddTaskFormInput();
}

void MAIN::Onlistkeydown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode()) {
	case WXK_DELETE:
		deleteselectedtask();
		break;
	case WXK_UP:
		MoveSelectedTask(-1);
		break;

	case WXK_DOWN:
		MoveSelectedTask(1);
		break;
	}
}


// when the application windows closed the tasks saved in file called tesks.txt
void MAIN::OnWindowsClosed(wxCloseEvent& evt)
{
	std::vector<Task> tasks;

	for (int i = 0; i < checklist->GetCount(); i++) {
		Task task;
		task.description = checklist->GetString(i);
		task.done = checklist->IsChecked(i);
		tasks.push_back(task);
	}
	SaveTasksToFile(tasks, "tasks.txt");
	evt.Skip();
}

// simply delete selected tasks 
void MAIN::deleteselectedtask()
{
	int SelectedIndex = checklist->GetSelection();

	if (SelectedIndex == wxNOT_FOUND) {
		return;
	}

	checklist->Delete(SelectedIndex);
}

// selection of tasks
void MAIN::MoveSelectedTask(int offset)
{
	int SelectedIndex = checklist->GetSelection();

	if (SelectedIndex == wxNOT_FOUND) {
		return;
	}

	int newIndex = SelectedIndex + offset;

	if (newIndex >= 0 && newIndex < checklist->GetCount()) {
		SwapTasks(SelectedIndex, newIndex);
		checklist->SetSelection(newIndex, true);
	}
}

// moving the task up or down
void MAIN::SwapTasks(int i, int j)
{
	Task taskI{ checklist->GetString(i).ToStdString(),checklist->IsChecked(i) };
	Task taskJ{ checklist->GetString(j).ToStdString(),checklist->IsChecked(j) };

	checklist->SetString(i, taskJ.description);
	checklist->Check(i, taskJ.done);

	checklist->SetString(j, taskI.description);
	checklist->Check(j, taskI.done);

}
