#pragma once
#include "GameEngine.h"

namespace RogueLike {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  healthBar;
	private: System::Windows::Forms::Label^  events;
	private: System::Windows::Forms::Label^  events2;
	private: System::Windows::Forms::Label^  lblLevel;
	private: System::Windows::Forms::Label^  lblGold;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->healthBar = (gcnew System::Windows::Forms::Label());
			this->events = (gcnew System::Windows::Forms::Label());
			this->events2 = (gcnew System::Windows::Forms::Label());
			this->lblLevel = (gcnew System::Windows::Forms::Label());
			this->lblGold = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(13, 13);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(200, 100);
			this->panel1->TabIndex = 0;
			// 
			// healthBar
			// 
			this->healthBar->AutoSize = true;
			this->healthBar->Location = System::Drawing::Point(237, 32);
			this->healthBar->Name = L"healthBar";
			this->healthBar->Size = System::Drawing::Size(38, 13);
			this->healthBar->TabIndex = 1;
			this->healthBar->Text = L"Health";
			// 
			// events
			// 
			this->events->AutoSize = true;
			this->events->Location = System::Drawing::Point(237, 54);
			this->events->Name = L"events";
			this->events->Size = System::Drawing::Size(50, 13);
			this->events->TabIndex = 2;
			this->events->Text = L"Exploring";
			// 
			// events2
			// 
			this->events2->AutoSize = true;
			this->events2->Location = System::Drawing::Point(237, 80);
			this->events2->Name = L"events2";
			this->events2->Size = System::Drawing::Size(0, 13);
			this->events2->TabIndex = 3;
			// 
			// lblLevel
			// 
			this->lblLevel->AutoSize = true;
			this->lblLevel->Location = System::Drawing::Point(240, 107);
			this->lblLevel->Name = L"lblLevel";
			this->lblLevel->Size = System::Drawing::Size(33, 13);
			this->lblLevel->TabIndex = 4;
			this->lblLevel->Text = L"Level";
			// 
			// lblGold
			// 
			this->lblGold->AutoSize = true;
			this->lblGold->Location = System::Drawing::Point(240, 124);
			this->lblGold->Name = L"lblGold";
			this->lblGold->Size = System::Drawing::Size(29, 13);
			this->lblGold->TabIndex = 5;
			this->lblGold->Text = L"Gold";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(50, 50);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 6;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(240, 151);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(256, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Arrow keys to move. \nSpace to fire fireball. \nP to pause";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkSalmon;
			this->ClientSize = System::Drawing::Size(436, 334);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->lblGold);
			this->Controls->Add(this->lblLevel);
			this->Controls->Add(this->events2);
			this->Controls->Add(this->events);
			this->Controls->Add(this->healthBar);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->Text = L"Rogue Like Dungeon Crawler";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		GameEngine^ gameEngine;

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {

		//start full screen
		WindowState = FormWindowState::Maximized;
		int panelWidth = Width - 250;
		int panelHeight = Height - 100;
		healthBar->Location = System::Drawing::Point(Width - 220, 32);
		events->Location = System::Drawing::Point(Width - 220, 58);
		events2->Location = System::Drawing::Point(Width - 220, 80);
		lblLevel->Location = System::Drawing::Point(Width - 220, 107);
		lblGold->Location = System::Drawing::Point(Width - 220, 124);
		label1->Location = System::Drawing::Point(Width - 220, 145);
		System::Diagnostics::Debug::WriteLine(panelWidth);
		System::Diagnostics::Debug::WriteLine(panelHeight);
		panel1->Size = System::Drawing::Size(panelWidth, panelHeight);
		pictureBox1->Size = System::Drawing::Size(Width, Height);
		pictureBox1->Visible = false;
		Graphics^ formCanvas = panel1->CreateGraphics();
		Random^ mainRandom = gcnew Random();
		gameEngine = gcnew GameEngine(formCanvas, mainRandom, panel1->Width, panel1->Height);

		timer1->Enabled = true;

	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		gameEngine->Run();
		healthBar->Text = "Health = " + gameEngine->GetHealth();
		events->Text = gameEngine->GetEvent();
		events2->Text = gameEngine->GetEvent2();
		lblLevel->Text = gameEngine->GetLevel();
		lblGold->Text = gameEngine->GetGold();
		if (gameEngine->PlayerAlive() == false)
		{
			timer1->Enabled = false;
			pictureBox1->Visible = true;

		}
	}
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		switch (e->KeyData)
		{
		case Keys::Left:
			gameEngine->UpdateDirection(WEST);
			break;
		case Keys::Up:
			gameEngine->UpdateDirection(NORTH);
			break;
		case Keys::Right:
			gameEngine->UpdateDirection(EAST);
			break;
		case Keys::Down:
			gameEngine->UpdateDirection(SOUTH);
			break;
		case Keys::P:
			if (timer1->Enabled == true)
			{
				timer1->Enabled = false;
			}
			else
			{
				timer1->Enabled = true;
			}
			break;
		case Keys::Space:
			if (gameEngine->rangeAttackMode == false )
			{
				gameEngine->rangeAttackMode = true;
				
			}
		default:
			break;
		}
	}
	};
}
