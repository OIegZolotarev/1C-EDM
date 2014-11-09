#pragma once

#include "DBAdapter.h"
#include "frmAddClient.h"
#include "frmAddProject.h"
#include "DBScanner.h"


namespace DbRegisterToolVS {

	static DialogResult ShowInputDialog(String ^% input,String^ prompt)
	{
		Drawing::Size size = System::Drawing::Size(640, 70);
		Form^ inputBox = gcnew Form();



		inputBox->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		inputBox->ClientSize = size;
		inputBox->Text = prompt;
		inputBox->StartPosition = FormStartPosition::CenterParent;

		Windows::Forms::TextBox^ textBox = gcnew TextBox();
		textBox->Size = System::Drawing::Size(size.Width - 10, 23);
		textBox->Location = System::Drawing::Point(5, 5);
		textBox->Text = input;
		inputBox->Controls->Add(textBox);

		Button^ okButton = gcnew Button();
		okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
		okButton->Name = "okButton";
		okButton->Size = System::Drawing::Size(75, 23);
		okButton->Text = "&OK";
		okButton->Location = System::Drawing::Point(size.Width - 80 - 80, 39);
		inputBox->Controls->Add(okButton);

		Button^ cancelButton = gcnew Button();
		cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		cancelButton->Name = "cancelButton";
		cancelButton->Size = System::Drawing::Size(75, 23);
		cancelButton->Text = "&Cancel";
		cancelButton->Location = System::Drawing::Point(size.Width - 80, 39);
		inputBox->Controls->Add(cancelButton);

		inputBox->AcceptButton = okButton;
		inputBox->CancelButton = cancelButton; 

		DialogResult result = inputBox->ShowDialog();
		input = textBox->Text;
		return result;
	}

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для frmMain
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(DBAdapter ^ db,array<String^>^ args);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~frmMain();
	private: System::Windows::Forms::CheckedListBox^  cbFoundDatabases;
	protected: 

	private: System::Windows::Forms::Label^  lbFoundDatabases;
	private: System::Windows::Forms::GroupBox^  gbAddTo;
	private: System::Windows::Forms::Button^  btAddProject;

	private: System::Windows::Forms::Label^  lbProject;
	private: System::Windows::Forms::ComboBox^  cbProjectsList;


	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  lbClientName;
	private: System::Windows::Forms::ComboBox^  cbClientsList;
	private: System::Windows::Forms::Button^  btAddBases;
	private: System::Windows::Forms::Button^  btCancel;

	private: System::Windows::Forms::Button^  btSelectAll;
	private: System::Windows::Forms::Button^  btUnselectAll;
	private: System::Windows::Forms::Button^  btInvert;

	protected: 

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->cbFoundDatabases = (gcnew System::Windows::Forms::CheckedListBox());
			this->lbFoundDatabases = (gcnew System::Windows::Forms::Label());
			this->gbAddTo = (gcnew System::Windows::Forms::GroupBox());
			this->btAddProject = (gcnew System::Windows::Forms::Button());
			this->lbProject = (gcnew System::Windows::Forms::Label());
			this->cbProjectsList = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->lbClientName = (gcnew System::Windows::Forms::Label());
			this->cbClientsList = (gcnew System::Windows::Forms::ComboBox());
			this->btAddBases = (gcnew System::Windows::Forms::Button());
			this->btCancel = (gcnew System::Windows::Forms::Button());
			this->btSelectAll = (gcnew System::Windows::Forms::Button());
			this->btUnselectAll = (gcnew System::Windows::Forms::Button());
			this->btInvert = (gcnew System::Windows::Forms::Button());
			this->gbAddTo->SuspendLayout();
			this->SuspendLayout();
			// 
			// cbFoundDatabases
			// 
			this->cbFoundDatabases->FormattingEnabled = true;
			this->cbFoundDatabases->Location = System::Drawing::Point(12, 27);
			this->cbFoundDatabases->Name = L"cbFoundDatabases";
			this->cbFoundDatabases->Size = System::Drawing::Size(349, 169);
			this->cbFoundDatabases->TabIndex = 0;
			// 
			// lbFoundDatabases
			// 
			this->lbFoundDatabases->AutoSize = true;
			this->lbFoundDatabases->Location = System::Drawing::Point(12, 8);
			this->lbFoundDatabases->Name = L"lbFoundDatabases";
			this->lbFoundDatabases->Size = System::Drawing::Size(156, 13);
			this->lbFoundDatabases->TabIndex = 1;
			this->lbFoundDatabases->Text = L"Обнаруженные базы данных:";
			// 
			// gbAddTo
			// 
			this->gbAddTo->Controls->Add(this->btAddProject);
			this->gbAddTo->Controls->Add(this->lbProject);
			this->gbAddTo->Controls->Add(this->cbProjectsList);
			this->gbAddTo->Controls->Add(this->button1);
			this->gbAddTo->Controls->Add(this->lbClientName);
			this->gbAddTo->Controls->Add(this->cbClientsList);
			this->gbAddTo->Location = System::Drawing::Point(12, 267);
			this->gbAddTo->Name = L"gbAddTo";
			this->gbAddTo->Size = System::Drawing::Size(349, 112);
			this->gbAddTo->TabIndex = 2;
			this->gbAddTo->TabStop = false;
			this->gbAddTo->Text = L"Добавить в";
			// 
			// btAddProject
			// 
			this->btAddProject->Location = System::Drawing::Point(308, 76);
			this->btAddProject->Name = L"btAddProject";
			this->btAddProject->Size = System::Drawing::Size(35, 23);
			this->btAddProject->TabIndex = 5;
			this->btAddProject->Text = L"+";
			this->btAddProject->UseVisualStyleBackColor = true;
			this->btAddProject->Click += gcnew System::EventHandler(this, &frmMain::btAddProject_Click);
			// 
			// lbProject
			// 
			this->lbProject->AutoSize = true;
			this->lbProject->Location = System::Drawing::Point(6, 61);
			this->lbProject->Name = L"lbProject";
			this->lbProject->Size = System::Drawing::Size(47, 13);
			this->lbProject->TabIndex = 4;
			this->lbProject->Text = L"Проект:";
			// 
			// cbProjectsList
			// 
			this->cbProjectsList->FormattingEnabled = true;
			this->cbProjectsList->Location = System::Drawing::Point(6, 77);
			this->cbProjectsList->Name = L"cbProjectsList";
			this->cbProjectsList->Size = System::Drawing::Size(295, 21);
			this->cbProjectsList->TabIndex = 3;
			this->cbProjectsList->SelectedIndexChanged += gcnew System::EventHandler(this, &frmMain::comboBox1_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(308, 31);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(35, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"+";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &frmMain::button1_Click);
			// 
			// lbClientName
			// 
			this->lbClientName->AutoSize = true;
			this->lbClientName->Location = System::Drawing::Point(6, 16);
			this->lbClientName->Name = L"lbClientName";
			this->lbClientName->Size = System::Drawing::Size(46, 13);
			this->lbClientName->TabIndex = 1;
			this->lbClientName->Text = L"Клиент:";
			// 
			// cbClientsList
			// 
			this->cbClientsList->FormattingEnabled = true;
			this->cbClientsList->Location = System::Drawing::Point(6, 32);
			this->cbClientsList->Name = L"cbClientsList";
			this->cbClientsList->Size = System::Drawing::Size(295, 21);
			this->cbClientsList->TabIndex = 0;
			this->cbClientsList->SelectedIndexChanged += gcnew System::EventHandler(this, &frmMain::cbClientsList_SelectedIndexChanged);
			// 
			// btAddBases
			// 
			this->btAddBases->Location = System::Drawing::Point(18, 395);
			this->btAddBases->Name = L"btAddBases";
			this->btAddBases->Size = System::Drawing::Size(131, 23);
			this->btAddBases->TabIndex = 3;
			this->btAddBases->Text = L"Добавить базы";
			this->btAddBases->UseVisualStyleBackColor = true;
			this->btAddBases->Click += gcnew System::EventHandler(this, &frmMain::btAddBases_Click);
			// 
			// btCancel
			// 
			this->btCancel->Location = System::Drawing::Point(230, 395);
			this->btCancel->Name = L"btCancel";
			this->btCancel->Size = System::Drawing::Size(131, 23);
			this->btCancel->TabIndex = 3;
			this->btCancel->Text = L"Отмена";
			this->btCancel->UseVisualStyleBackColor = true;
			// 
			// btSelectAll
			// 
			this->btSelectAll->Location = System::Drawing::Point(12, 203);
			this->btSelectAll->Name = L"btSelectAll";
			this->btSelectAll->Size = System::Drawing::Size(94, 23);
			this->btSelectAll->TabIndex = 4;
			this->btSelectAll->Text = L"Выбрать все";
			this->btSelectAll->UseVisualStyleBackColor = true;
			this->btSelectAll->Click += gcnew System::EventHandler(this, &frmMain::btSelectAll_Click);
			// 
			// btUnselectAll
			// 
			this->btUnselectAll->Location = System::Drawing::Point(112, 203);
			this->btUnselectAll->Name = L"btUnselectAll";
			this->btUnselectAll->Size = System::Drawing::Size(94, 23);
			this->btUnselectAll->TabIndex = 4;
			this->btUnselectAll->Text = L"Снять все";
			this->btUnselectAll->UseVisualStyleBackColor = true;
			this->btUnselectAll->Click += gcnew System::EventHandler(this, &frmMain::btUnselectAll_Click);
			// 
			// btInvert
			// 
			this->btInvert->Location = System::Drawing::Point(212, 203);
			this->btInvert->Name = L"btInvert";
			this->btInvert->Size = System::Drawing::Size(149, 23);
			this->btInvert->TabIndex = 4;
			this->btInvert->Text = L"Обратить выделение";
			this->btInvert->UseVisualStyleBackColor = true;
			this->btInvert->Click += gcnew System::EventHandler(this, &frmMain::btInvert_Click);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(375, 428);
			this->Controls->Add(this->btInvert);
			this->Controls->Add(this->btUnselectAll);
			this->Controls->Add(this->btSelectAll);
			this->Controls->Add(this->btCancel);
			this->Controls->Add(this->btAddBases);
			this->Controls->Add(this->gbAddTo);
			this->Controls->Add(this->lbFoundDatabases);
			this->Controls->Add(this->cbFoundDatabases);
			this->Name = L"frmMain";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Регистрация базы данных";
			this->Load += gcnew System::EventHandler(this, &frmMain::frmMain_Load);
			this->gbAddTo->ResumeLayout(false);
			this->gbAddTo->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



	private: 
		DBAdapter ^ m_DBAdapter;

		void RefereshClientsList();
		void RefreshProjectList();

		void ScanBasesList(String ^ path);

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btAddProject_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void cbClientsList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void btSelectAll_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btUnselectAll_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btInvert_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void btAddBases_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void frmMain_Load(System::Object^  sender, System::EventArgs^  e);
};
}
