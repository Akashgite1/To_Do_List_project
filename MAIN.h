#pragma once
#include<wx/wx.h>


class MAIN : public wxFrame
{
public:

	MAIN(const wxString& title);

private:
	void CreateControls();
	void BindEventHandlers();
	void AddSavedTasks();

	void OnAddButtonClicked(wxCommandEvent& evt);
	void OnInputEnter(wxCommandEvent& evt);
	void Onlistkeydown(wxKeyEvent& evt);
	void OnClearButtonClicked(wxCommandEvent& evt);
	void OnWindowsClosed(wxCloseEvent& evt);

	void AddTaskFormInput();
	void deleteselectedtask();
	void MoveSelectedTask(int offset);
	void SwapTasks(int i, int j);


	wxPanel* panel;
	wxStaticText* headtext;
	wxTextCtrl* inputfield;
	wxButton* addbutton;
	wxCheckListBox* checklist;
	wxButton* clearbutton;
};

