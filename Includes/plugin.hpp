#pragma once

using Fptr = void(*)();
void new_entry(const std::string& name, Fptr cheat);
void new_entry_with_note(const std::string& name, const std::string& note, Fptr cheat);

void new_radio_entry(int group, const std::string& name, Fptr cheat);
void new_radio_entry_with_note(int group, const std::string& name, const std::string &note, Fptr cheat);

void new_spoiler(const std::string& name);
void new_spoiler_with_note(const std::string& name, const std::string& note);

void exit_spoiler();
