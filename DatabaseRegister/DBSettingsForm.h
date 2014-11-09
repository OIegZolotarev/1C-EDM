#pragma once

#include "DatabaseRegister.h"

namespace DatabaseRegister {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для DBSettingsForm
	/// </summary>
	public ref class DBSettingsForm : public System::Windows::Forms::Form
	{
	public:
		DBSettingsForm(EnterpriseDatabase ^ db)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//

			cbEnterpriseVersion->Items->Clear();

			EnterpriseVersionDescriptor ^ newest = nullptr;

			for each(EnterpriseVersionDescriptor ^ d in PlatformManager::GetPlatformList())
			{
				cbEnterpriseVersion->Items->Add(d);

				if (!newest) 
				{
					newest = d;
					cbEnterpriseVersion->SelectedIndex = cbEnterpriseVersion->Items->Count - 1;
				}
				else
				{
					if (newest->Older(d))
					{
						newest = d;
						cbEnterpriseVersion->SelectedIndex = cbEnterpriseVersion->Items->Count - 1;
					}
				}

			}
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~DBSettingsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  gbDefaultLaunchMode;
	protected: 
	private: System::Windows::Forms::RadioButton^  rbThinClient;
	private: System::Windows::Forms::RadioButton^  rbThickClient;
	private: System::Windows::Forms::RadioButton^  rbDefault;
	private: System::Windows::Forms::ComboBox^  cbEnterpriseVersion;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  gbBasePath;
	private: System::Windows::Forms::Button^  btSetupPath;
	private: System::Windows::Forms::TextBox^  tbDatabasePath;

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
			this->gbDefaultLaunchMode = (gcnew System::Windows::Forms::GroupBox());
			this->rbThinClient = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->cbEnterpriseVersion = (gcnew System::Windows::Forms::ComboBox());
			this->rbThickClient = (gcnew System::Windows::Forms::RadioButton());
			this->rbDefault = (gcnew System::Windows::Forms::RadioButton());
			this->gbBasePath = (gcnew System::Windows::Forms::GroupBox());
			this->btSetupPath = (gcnew System::Windows::Forms::Button());
			this->tbDatabasePath = (gcnew System::Windows::Forms::TextBox());
			this->btOk = (gcnew System::Windows::Forms::Button());
			this->btCancel = (gcnew System::Windows::Forms::Button());
			this->gbDefaultLaunchMode->SuspendLayout();
			this->gbBasePath->SuspendLayout();
			this->SuspendLayout();
			// 
			// gbDefaultLaunchMode
			// 
			this->gbDefaultLaunchMode->Controls->Add(this->rbThinClient);
			this->gbDefaultLaunchMode->Controls->Add(this->label1);
			this->gbDefaultLaunchMode->Controls->Add(this->cbEnterpriseVersion);
			this->gbDefaultLaunchMode->Controls->Add(this->rbThickClient);
			this->gbDefaultLaunchMode->Controls->Add(this->rbDefault);
			this->gbDefaultLaunchMode->Location = System::Drawing::Point(12, 170);
			this->gbDefaultLaunchMode->Name = L"gbDefaultLaunchMode";
			this->gbDefaultLaunchMode->Size = System::Drawing::Size(322, 150);
			this->gbDefaultLaunchMode->TabIndex = 0;
			this->gbDefaultLaunchMode->TabStop = false;
			this->gbDefaultLaunchMode->Text = L"Основной режим запуска:";
			// 
			// rbThinClient
			// 
			this->rbThinClient->AutoSize = true;
			this->rbThinClient->Location = System::Drawing::Point(6, 65);
			this->rbThinClient->Name = L"rbThinClient";
			this->rbThinClient->Size = System::Drawing::Size(100, 17);
			this->rbThinClient->TabIndex = 0;
			this->rbThinClient->Text = L"Тонкий клиент";
			this->rbThinClient->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 97);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(109, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Версия платформы:";
			// 
			// cbEnterpriseVersion
			// 
			this->cbEnterpriseVersion->FormattingEnabled = true;
			this->cbEnterpriseVersion->Location = System::Drawing::Point(9, 113);
			this->cbEnterpriseVersion->Name = L"cbEnterpriseVersion";
			this->cbEnterpriseVersion->Size = System::Drawing::Size(307, 21);
			this->cbEnterpriseVersion->TabIndex = 1;
			// 
			// rbThickClient
			// 
			this->rbThickClient->AutoSize = true;
			this->rbThickClient->Location = System::Drawing::Point(6, 42);
			this->rbThickClient->Name = L"rbThickClient";
			this->rbThickClient->Size = System::Drawing::Size(107, 17);
			this->rbThickClient->TabIndex = 0;
			this->rbThickClient->Text = L"Толстый клиент";
			this->rbThickClient->UseVisualStyleBackColor = true;
			// 
			// rbDefault
			// 
			this->rbDefault->AutoSize = true;
			this->rbDefault->Checked = true;
			this->rbDefault->Location = System::Drawing::Point(6, 19);
			this->rbDefault->Name = L"rbDefault";
			this->rbDefault->Size = System::Drawing::Size(155, 17);
			this->rbDefault->TabIndex = 0;
			this->rbDefault->TabStop = true;
			this->rbDefault->Text = L"Выбирать автоматически";
			this->rbDefault->UseVisualStyleBackColor = true;
			// 
			// gbBasePath
			// 
			this->gbBasePath->Controls->Add(this->btSetupPath);
			this->gbBasePath->Controls->Add(this->tbDatabasePath);
			this->gbBasePath->Location = System::Drawing::Point(12, 12);
			this->gbBasePath->Name = L"gbBasePath";
			this->gbBasePath->Size = System::Drawing::Size(322, 100);
			this->gbBasePath->TabIndex = 3;
			this->gbBasePath->TabStop = false;
			this->gbBasePath->Text = L"Расположение:";
			this->gbBasePath->Enter += gcnew System::EventHandler(this, &DBSettingsForm::groupBox1_Enter);
			// 
			// btSetupPath
			// 
			this->btSetupPath->Location = System::Drawing::Point(9, 57);
			this->btSetupPath->Name = L"btSetupPath";
			this->btSetupPath->Size = System::Drawing::Size(307, 23);
			this->btSetupPath->TabIndex = 1;
			this->btSetupPath->Text = L"Указать каталог...";
			this->btSetupPath->UseVisualStyleBackColor = true;
			this->btSetupPath->Click += gcnew System::EventHandler(this, &DBSettingsForm::btSetupPath_Click);
			// 
			// tbDatabasePath
			// 
			this->tbDatabasePath->Location = System::Drawing::Point(6, 30);
			this->tbDatabasePath->Name = L"tbDatabasePath";
			this->tbDatabasePath->Size = System::Drawing::Size(310, 20);
			this->tbDatabasePath->TabIndex = 0;
			// 
			// btOk
			// 
			this->btOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btOk->Location = System::Drawing::Point(13, 326);
			this->btOk->Name = L"btOk";
			this->btOk->Size = System::Drawing::Size(75, 23);
			this->btOk->TabIndex = 4;
			this->btOk->Text = L"Ок";
			this->btOk->UseVisualStyleBackColor = true;
			this->btOk->Click += gcnew System::EventHandler(this, &DBSettingsForm::button1_Click);
			// 
			// btCancel
			// 
			this->btCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btCancel->Location = System::Drawing::Point(265, 326);
			this->btCancel->Name = L"btCancel";
			this->btCancel->Size = System::Drawing::Size(75, 23);
			this->btCancel->TabIndex = 4;
			this->btCancel->Text = L"Отмена";
			this->btCancel->UseVisualStyleBackColor = true;
			// 
			// DBSettingsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(352, 361);
			this->Controls->Add(this->btCancel);
			this->Controls->Add(this->btOk);
			this->Controls->Add(this->gbBasePath);
			this->Controls->Add(this->gbDefaultLaunchMode);
			this->Name = L"DBSettingsForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Настройки для базы данных";
			this->gbDefaultLaunchMode->ResumeLayout(false);
			this->gbDefaultLaunchMode->PerformLayout();
			this->gbBasePath->ResumeLayout(false);
			this->gbBasePath->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void btSetupPath_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	};
}
