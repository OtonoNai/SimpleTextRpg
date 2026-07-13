#include <iostream>
#include "CSVReader.h"
#include <Windows.h>
#include <conio.h>
#include <format>
#include <array>
#include <sstream>
#include <map>

using namespace std;

enum DataRow {
	line,
	raw_text,
	io_type,
	var_names,
	num_of_vars,
	var_type,
	var_range,
	interact_type,
	interact_category,
	interact_with,
	_end,
};

struct TextDataView {
	string data;
};

struct TextDataIn {
	int column;
	int var_x;
	string var_name;
	string var_type;
	string var_range;
};

struct TextDataUpdate {
	int line;
};

struct TextDataInteract {
	int index;
	string text;
};

struct TextData {
public:
	static constexpr int num_of_row = DataRow::_end;

	static const char border_text = '=';
	static const int border_length = 40;

	vector<array<string, num_of_row>>& GetDataOrigin() {
		return text_data_origin;
	}
	void SetDataOrigin(vector<array<string, num_of_row>> _data) {
		text_data_origin = _data;
	}

	void SetHasSelect(bool _value) {
		has_select = _value;
	}

	bool CheckHasSelect() {
		return has_select;
	}

	vector<array<string, num_of_row>> text_data_origin;
	vector<TextDataView> view;
	vector<TextDataIn> in;
	vector<TextDataUpdate> update;

private:
	bool has_select = false;
};

struct SeparatedData {
	vector<TextDataView> view;
	vector<TextDataIn> inputs;
	vector<TextDataUpdate> updates;
	vector<TextDataInteract> selects;
};

class Item {
	string name;
	string interact_with;

};

struct Inventory {

};

class Player {
private:
	map<string, string> status;
	bool isValidStatus = false;

public:
	map<string, string> GetAllStatus() {
		return status;
	}

	string GetStatusFromKey(string _key) {
		return status[_key];
	}

	void SetStatus(string _key, string _value) {
		status[_key] = _value;
	}

	bool GetIsValidStatus() {
		return isValidStatus;
	}

	void SetIsValidStatus(bool _value) {
		isValidStatus = _value;
	}
};

void MoveCursor(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		pos
	);
}

vector<array<string, TextData::num_of_row>> ReadCSV(string _fileName, vector<array<string, TextData::num_of_row>> _list) {
	CSVReader reader;
	reader.ReadFile(format("./Data/{}.csv", _fileName));
	array<string, TextData::num_of_row> temp;

	for (int i = 0; i < reader.GetRowCount(); ++i) {
		auto& row = reader.GetRow(i);
		for (int j = 0; j < row.size(); ++j) {
			temp[j] = row[j];
		}
		_list.push_back(temp);
	}

	return _list;
}

string GetBorder() {
	string temp;
	for (int i = 0; i < TextData::border_length; ++i) {
		temp += TextData::border_text;
	}
	return temp;
}

string GetEmpty() {
	return " ";
}

string ClearLine() {
	string temp;
	for (int i = 0; i < 80; ++i) {
		temp += ' ';
	}
	return temp;
}

SeparatedData SeparateText(vector<array<string, TextData::num_of_row>> _list) {
	vector<TextDataView> view;
	vector<TextDataIn> inputs;
	vector<TextDataUpdate> updates;
	vector<TextDataInteract> interacts;

	for (int i = 0; i < _list.size(); ++i) {
		TextDataView temp_view;
		if (_list[i][1] == "border") {
			temp_view.data = GetBorder();
			view.push_back(temp_view);
			continue;
		}
		else if (_list[i][1] == "empty") {
			temp_view.data = GetEmpty();
			view.push_back(temp_view);
			continue;
		}
		else {
			int screen_line = static_cast<int>(view.size());

			if (_list[i][2] == "in") {
				TextDataIn temp_input;

				temp_input.column = screen_line;
				temp_input.var_name = _list[i][DataRow::var_names];
				temp_input.var_type = _list[i][DataRow::var_type];
				temp_input.var_range = _list[i][DataRow::var_range];

				inputs.push_back(temp_input);
			}
			else if (_list[i][2] == "update") {
				TextDataUpdate temp_update;

				temp_update.line = stoi(_list[i][DataRow::line]);

				updates.push_back(temp_update);
			}
			else if (_list[i][2] == "interact") {
				TextDataInteract temp_interacts;

				temp_interacts.index = stoi(_list[i][DataRow::line]);
				temp_interacts.text = _list[i][1];
				continue;
			}

			temp_view.data = _list[i][1];
		}

		view.push_back(temp_view);
	}

	SeparatedData result{
		view,
		inputs,
		updates,
		interacts,
	};

	return result;
}

void LoadTextData(TextData& _data, int _phase) {
	_data.SetDataOrigin(ReadCSV(format("TextData{}", _phase), _data.GetDataOrigin()));
}

void BuildData(TextData& _data) {
	SeparatedData temp = SeparateText(_data.GetDataOrigin());

	_data.view = temp.view;
	_data.in = temp.inputs;
	_data.update = temp.updates;

}

void InitRender(TextData& _data) {
	vector<TextDataView> temp = _data.view;
	for (int i = 1; i < temp.size(); ++i) {
		cout << temp[i].data;

		for (auto& input : _data.in) {
			if (input.column == i) {
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
				input.var_x = csbi.dwCursorPosition.X;
				break;
			}
		}
		cout << endl;
	}
}

bool CheckInputIsValid(string _value, vector<int> _range, int _x, int _y) {
	int value = stoi(_value);

	if (value >= _range[0] && value <= _range[1]) {
		return true;
	}
	else {
		MoveCursor(_x + 1, _y - 1);
		cout << "범위를 벗어났습니다. " << _range[0] << "부터 " << _range[1] << " 사이의 값을 입력해주세요.";
		Sleep(1000);
		MoveCursor(_x + 1, _y - 1);
		cout << ClearLine();
		return false;
	}
}

void GetInput(TextData& _data, Player& _player, int _phase) {
	vector<TextDataView> temp_veiw = _data.view;
	vector<TextDataIn> temp_in = _data.in;
	string temp_data;

	for (const auto& input : temp_in) {
	RETRY_INPUT:
		stringstream ss(input.var_range);
		string token;
		string temp_type;
		vector<int> temp_range;

		temp_type = input.var_type;

		int y = input.column;
		int x = input.var_x;

		MoveCursor(x + 1, y - 1);

		string value;
		getline(cin, value);

		try
		{
			if (temp_type == "int") {
				while (getline(ss, token, '-')) {
					temp_range.push_back(stoi(token));
				}

				if (!CheckInputIsValid(value, temp_range, x, y)) {
					goto RETRY_INPUT;
				}
			}
		}
		catch (const std::invalid_argument&)
		{
			MoveCursor(x + 1, y - 1);
			cout << "숫자만 입력하세요.";
			Sleep(1000);
			MoveCursor(x + 1, y - 1);
			cout << ClearLine();
			goto RETRY_INPUT;
		}

		if (_phase == 1) {
			_player.SetStatus(input.var_name, value);
		}
		else if (_phase == 2) {

		}
	}
}

void Interact(TextData& _data, Player& _player) {

}

void UpdateRender(TextData& _data, Player& _player) {
	vector<TextDataView> temp_view = _data.view;
	vector<TextDataUpdate> temp_update = _data.update;
	int fix_y_pos = 1;

	for (const auto& args : temp_update) {
		string text_origin = _data.view[args.line].data;
		size_t t_start = 0;
		while ((t_start = text_origin.find("{", t_start)) != string::npos) {
			size_t t_end = text_origin.find("}", t_start);

			if (t_end == string::npos) {
				break;
			}

			string var = text_origin.substr(t_start + 1, t_end - t_start - 1);
			string value = _player.GetStatusFromKey(var);
			text_origin.replace(t_start, t_end - t_start + 1, value);
			t_start += value.length();
		}

		MoveCursor(0, args.line - fix_y_pos);
		cout << ClearLine();
		MoveCursor(0, args.line - fix_y_pos);
		cout << text_origin;
	}
}

void WaitLoading(string _text, TextData& _data) {
	string exit_text = "종료하려면 exit을 입력하세요.";
	string step_text = "계속하려면 아무 문자열이나 입력하세요.";
	int fix_y_pos = 2;
	MoveCursor(0, (unsigned int)_data.view.size() - fix_y_pos);
	cout << ClearLine();
	MoveCursor(0, (unsigned int)_data.view.size() - fix_y_pos);
	cout << "/" << _text;
	for (int i = 0; i < 3; ++i) {
		Sleep(500);
		cout << ". ";
	}
	cout << "/" << endl;
	Sleep(500);
	MoveCursor(0, (unsigned int)_data.view.size() - fix_y_pos);
	cout << ClearLine();
	MoveCursor(0, (unsigned int)_data.view.size() - fix_y_pos);
	cout << "Loaded!" << endl;
	MoveCursor(0, (unsigned int)_data.view.size() - fix_y_pos + 1);
	cout << exit_text << endl;
	cout << step_text << endl;
}

bool CheckExit() {
	string input;
	cin >> input;

	if (input == "exit") {
		return true;
	}
	else {
		return false;
	}
}

void SetNext(TextData& _data, int& _phase) {
	_data.GetDataOrigin().clear();
	MoveCursor(0, (unsigned int)_data.view.size() + 1);
	++_phase;
	if (CheckExit()) {
		exit(0);
	}
}

void ClearConsole() {
	system("cls");
	MoveCursor(0, 0);
}

int main()
{
	TextData text_data;
	Player player;
	int phase = 1;

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	while (true) {
		ClearConsole();
		LoadTextData(text_data, phase);
		BuildData(text_data);
		InitRender(text_data);
		GetInput(text_data, player, phase);
		WaitLoading("Update", text_data);
		UpdateRender(text_data, player);
		SetNext(text_data, phase);
	}
}