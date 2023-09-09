#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class ImGuiTheme {
public:

	ImVec4 m_Primary = ImVec4(1.0, 1.0, 1.0, 0.2);
	ImVec4 m_Secondary = ImVec4(0.1, 0.1, 0.1, 1.0);
	ImVec4 m_Tertiary = ImVec4(0.0, 0.0, 0.0, 1.0);
	ImVec4* colours = ImGui::GetStyle().Colors;

	void changePallette(ImVec4 primary, ImVec4 secondary = ImVec4(0.1, 0.1, 0.1, 1), ImVec4 tertiary = ImVec4(0.0, 0.0, 0.0, 1)){
		
		m_Primary = primary;
		m_Secondary = secondary;
		m_Tertiary = tertiary;
		
		colours[ImGuiCol_TitleBg] = m_Primary;
		colours[ImGuiCol_TitleBgActive] = m_Primary;
		colours[ImGuiCol_TitleBgCollapsed] = m_Tertiary;

		colours[ImGuiCol_Header] = m_Tertiary;
		colours[ImGuiCol_HeaderActive] = m_Tertiary;
		colours[ImGuiCol_HeaderHovered] = m_Secondary;

		colours[ImGuiCol_CheckMark] = m_Primary;

		colours[ImGuiCol_FrameBg] = m_Secondary;
		colours[ImGuiCol_FrameBgActive] = m_Secondary;
		colours[ImGuiCol_FrameBgHovered] = m_Secondary;

		colours[ImGuiCol_ButtonActive] = m_Tertiary;;
		colours[ImGuiCol_Button] = m_Tertiary;;
		colours[ImGuiCol_ButtonHovered] = m_Secondary;

		colours[ImGuiCol_SliderGrab] = m_Primary;
		colours[ImGuiCol_SliderGrabActive] = m_Primary;
	};

	// Setting specific colours to GUI components

};