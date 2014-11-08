#pragma once

#include "DBAdapter.h"

namespace DbRegisterToolVS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	

	/// <summary>
	/// Сводка для frmAddProject
	/// </summary>
	public ref class frmAddProject : public System::Windows::Forms::Form
	{

		DBAdapter ^ m_DBAdapter;
		DBClient ^ m_Filter;
	public:
		frmAddProject(DBAdapter ^ adapter,DBClient ^ filter)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			
			m_DBAdapter = adapter;
			m_Filter = filter;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~frmAddProject()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  cbClientsList;
	protected: 

	private: System::Windows::Forms::Label^  lbClient;
	private: System::Windows::Forms::Button^  btOk;
	private: System::Windows::Forms::Button^  btCancel;
	private: System::Windows::Forms::TextBox^  edTitle;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  edDescription;
	private: System::Windows::Forms::Label^  label2;
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
			this->cbClientsList = (gcnew System::Windows::Forms::ComboBox());
			this->lbClient = (gcnew System::Windows::Forms::Label());
			this->btOk = (gcnew System::Windows::Forms::Button());
			this->btCancel = (gcnew System::Windows::Forms::Button());
			this->edTitle = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->edDescription = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// cbClientsList
			// 
			this->cbClientsList->FormattingEnabled = true;
			this->cbClientsList->Location = System::Drawing::Point(12, 38);
			this->cbClientsList->Name = L"cbClientsList";
			this->cbClientsList->Size = System::Drawing::Size(260, 21);
			this->cbClientsList->TabIndex = 0;
			// 
			// lbClient
			// 
			this->lbClient->AutoSize = true;
			this->lbClient->Location = System::Drawing::Point(13, 19);
			this->lbClient->Name = L"lbClient";
			this->lbClient->Size = System::Drawing::Size(46, 13);
			this->lbClient->TabIndex = 1;
			this->lbClient->Text = L"Клиент:";
			// 
			// btOk
			// 
			this->btOk->Location = System::Drawing::Point(12, 227);
			this->btOk->Name = L"btOk";
			this->btOk->Size = System::Drawing::Size(75, 23);
			this->btOk->TabIndex = 2;
			this->btOk->Text = L"Ok";
			this->btOk->UseVisualStyleBackColor = true;
			this->btOk->Click += gcnew System::EventHandler(this, &frmAddProject::btOk_Click);
			// 
			// btCancel
			// 
			this->btCancel->Location = System::Drawing::Point(196, 227);
			this->btCancel->Name = L"btCancel";
			this->btCancel->Size = System::Drawing::Size(75, 23);
			this->btCancel->TabIndex = 3;
			this->btCancel->Text = L"Отмена";
			this->btCancel->UseVisualStyleBackColor = true;
			this->btCancel->Click += gcnew System::EventHandler(this, &frmAddProject::btCancel_Click);
			// 
			// edTitle
			// 
			this->edTitle->Location = System::Drawing::Point(12, 88);
			this->edTitle->Name = L"edTitle";
			this->edTitle->Size = System::Drawing::Size(256, 20);
			this->edTitle->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 72);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Название:";
			// 
			// edDescription
			// 
			this->edDescription->Location = System::Drawing::Point(12, 139);
			this->edDescription->Multiline = true;
			this->edDescription->Name = L"edDescription";
			this->edDescription->Size = System::Drawing::Size(256, 67);
			this->edDescription->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 123);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Описание:";
			// 
			// frmAddProject
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->edDescription);
			this->Controls->Add(this->edTitle);
			this->Controls->Add(this->btCancel);
			this->Controls->Add(this->btOk);
			this->Controls->Add(this->lbClient);
			this->Controls->Add(this->cbClientsList);
			this->Name = L"frmAddProject";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Добавление проекта";
			this->Load += gcnew System::EventHandler(this, &frmAddProject::frmAddProject_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void RefreshClientsList();
		
	private: System::Void btOk_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if (edTitle->Text == "")
				 {
					 return;
				 }

				 DBClient ^ c = (DBClient^)cbClientsList->SelectedItem;

				 if (c != nullptr)
				 {
					 DBProject ^ p = gcnew DBProject();
					 p->m_DBClient = c;
					 p->m_strDescription = edDescription->Text;
					 p->m_strTitle = edTitle->Text;
					 m_DBAdapter->RegisterProject(p);
					 					 
					 Close();
				 }
				 
			 }
private: System::Void frmAddProject_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			 RefreshClientsList();
		 }
private: System::Void btCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			 Close();
		 }
};
}
