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
	/// Сводка для frmAddClient
	/// </summary>frmAddClient
	public ref class frmAddClient : public System::Windows::Forms::Form
	{

		DBAdapter ^ m_DBAdapater;

	public:
		frmAddClient(DBAdapter ^ dbAdapter)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			
			m_DBAdapater = dbAdapter;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~frmAddClient()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  edClientName;
	protected: 

	protected: 
	private: System::Windows::Forms::Label^  lbAddClientText;
	private: System::Windows::Forms::Button^  btOk;
	private: System::Windows::Forms::Button^  btCancel;

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
			this->edClientName = (gcnew System::Windows::Forms::TextBox());
			this->lbAddClientText = (gcnew System::Windows::Forms::Label());
			this->btOk = (gcnew System::Windows::Forms::Button());
			this->btCancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// edClientName
			// 
			this->edClientName->Location = System::Drawing::Point(12, 31);
			this->edClientName->Name = L"edClientName";
			this->edClientName->Size = System::Drawing::Size(260, 20);
			this->edClientName->TabIndex = 0;
			// 
			// lbAddClientText
			// 
			this->lbAddClientText->AutoSize = true;
			this->lbAddClientText->Location = System::Drawing::Point(9, 15);
			this->lbAddClientText->Name = L"lbAddClientText";
			this->lbAddClientText->Size = System::Drawing::Size(32, 13);
			this->lbAddClientText->TabIndex = 1;
			this->lbAddClientText->Text = L"Имя:";
			// 
			// btOk
			// 
			this->btOk->Location = System::Drawing::Point(12, 66);
			this->btOk->Name = L"btOk";
			this->btOk->Size = System::Drawing::Size(75, 23);
			this->btOk->TabIndex = 2;
			this->btOk->Text = L"Ok";
			this->btOk->UseVisualStyleBackColor = true;
			this->btOk->Click += gcnew System::EventHandler(this, &frmAddClient::btOk_Click);
			// 
			// btCancel
			// 
			this->btCancel->Location = System::Drawing::Point(197, 66);
			this->btCancel->Name = L"btCancel";
			this->btCancel->Size = System::Drawing::Size(75, 23);
			this->btCancel->TabIndex = 2;
			this->btCancel->Text = L"Отмена";
			this->btCancel->UseVisualStyleBackColor = true;
			this->btCancel->Click += gcnew System::EventHandler(this, &frmAddClient::btCancel_Click);
			// 
			// frmAddClient
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 101);
			this->Controls->Add(this->btCancel);
			this->Controls->Add(this->btOk);
			this->Controls->Add(this->lbAddClientText);
			this->Controls->Add(this->edClientName);
			this->MaximizeBox = false;
			this->Name = L"frmAddClient";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Добавление клиента";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btOk_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 
				 if (edClientName->Text == "") 
				 {					 
					 return;
				 }

				 auto CmdText = String::Format("INSERT INTO Clients (rowid,name) values(NULL,\"{0}\")",edClientName->Text);
				 SQLiteCommand ^ c = gcnew SQLiteCommand(CmdText,m_DBAdapater->GetDBConnetion());
				 c->ExecuteNonQuery();

				 Close();
			 }
	private: System::Void btCancel_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 Close();
			 }
};
}
