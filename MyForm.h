#pragma once

#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib,"opencv_world430d.lib")	/*opencv_world430.libにリンク*/
#else
#pragma comment(lib,"opencv_world430.lib")	/*opencv_world430.libにリンク*/
#endif

#include <mat2bmp.h>

namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	//Add
	using namespace cv;

	Mat	mSrc;					/*最初に開いたオリジナル画像*/
	Mat	mEdit;					/*編集中の画像*/
	cv::Point mStartPoint;		/*マウスクリックの始点*/


	///
	/// 挿入する図形の種類
	///
	enum INSERT_TYPE {
		INSERT_TYPE_NONE = 0,	/*初期値*/
		INSERT_TYPE_CIRCLE,		/*円*/
		INSERT_TYPE_RECTANGLE,	/*四角*/
		INSERT_TYPE_LINE,		/*線*/
		INSERT_TYPE_TEXT,		/*文字*/
	};
	INSERT_TYPE mInsertType;	/*挿入する図形の型を記憶*/

	/// <summary>
	/// MyForm の概要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
			this->Text = "ファイル";

			panel1->Dock = DockStyle::Fill;	/*コンテナとなるコントロールの描画領域全体を埋める */
			panel1->AutoScroll = true;

			/*pictureBox1の初期設定*/
			pictureBox1->Location = System::Drawing::Point(0, 0);	/* PictureBoxコントロールの位置(始点) */
			pictureBox1->SizeMode = PictureBoxSizeMode::AutoSize;	/* PictureBoxに格納するイメージと同じ大きさになる */

			/*マウスクリックのイベントハンドらの登録*/
			pictureBox1->MouseDown += gcnew MouseEventHandler(this, &MyForm::myMouseDown);

		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  FileMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  FileMenu_Open;
	private: System::Windows::Forms::ToolStripMenuItem^  FileMenu_Close;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  FileMenu_SaveAs;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenu_Reverse;

	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenu_Reverse_TopBottom;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenu_Reverse_LeftRight;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenu_Resize;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenu_Rotate;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenuRotate_90;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenu_Rotate_270;
	private: System::Windows::Forms::ToolStripMenuItem^  FileMenu_Initialize;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenu_Insert;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenuInsert_circle;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenuInsert_rectangle;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenuInsert_line;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolMenuInsert_text;


	protected:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->FileMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FileMenu_Open = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FileMenu_SaveAs = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FileMenu_Initialize = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->FileMenu_Close = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenu_Reverse = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenu_Reverse_TopBottom = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenu_Reverse_LeftRight = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenu_Resize = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenu_Rotate = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenuRotate_90 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenu_Rotate_270 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenu_Insert = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenuInsert_circle = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenuInsert_rectangle = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenuInsert_line = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolMenuInsert_text = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->FileMenu, this->ToolMenu });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(511, 26);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// FileMenu
			// 
			this->FileMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->FileMenu_Open,
					this->FileMenu_SaveAs, this->FileMenu_Initialize, this->FileMenu_Close
			});
			this->FileMenu->Name = L"FileMenu";
			this->FileMenu->Size = System::Drawing::Size(85, 22);
			this->FileMenu->Text = L"ファイル(&F)";
			this->FileMenu->Click += gcnew System::EventHandler(this, &MyForm::FileMenu_Click);
			// 
			// FileMenu_Open
			// 
			this->FileMenu_Open->Name = L"FileMenu_Open";
			this->FileMenu_Open->Size = System::Drawing::Size(190, 22);
			this->FileMenu_Open->Text = L"開く(&O)";
			this->FileMenu_Open->Click += gcnew System::EventHandler(this, &MyForm::FileMenu_Open_Click);
			// 
			// FileMenu_SaveAs
			// 
			this->FileMenu_SaveAs->Name = L"FileMenu_SaveAs";
			this->FileMenu_SaveAs->Size = System::Drawing::Size(190, 22);
			this->FileMenu_SaveAs->Text = L"名前を付けて保存(&A)";
			this->FileMenu_SaveAs->Click += gcnew System::EventHandler(this, &MyForm::FileMenu_SaveAs_Click);
			// 
			// FileMenu_Initialize
			// 
			this->FileMenu_Initialize->Name = L"FileMenu_Initialize";
			this->FileMenu_Initialize->Size = System::Drawing::Size(190, 22);
			this->FileMenu_Initialize->Text = L"初期状態に戻す(&I)";
			this->FileMenu_Initialize->Click += gcnew System::EventHandler(this, &MyForm::FileMenu_Initialize_Click);
			// 
			// FileMenu_Close
			// 
			this->FileMenu_Close->Name = L"FileMenu_Close";
			this->FileMenu_Close->Size = System::Drawing::Size(190, 22);
			this->FileMenu_Close->Text = L"閉じる(&C)";
			this->FileMenu_Close->Click += gcnew System::EventHandler(this, &MyForm::FileMenu_Close_Click);
			// 
			// ToolMenu
			// 
			this->ToolMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ToolMenu_Reverse,
					this->ToolMenu_Resize, this->ToolMenu_Rotate, this->ToolMenu_Insert
			});
			this->ToolMenu->Name = L"ToolMenu";
			this->ToolMenu->Size = System::Drawing::Size(74, 22);
			this->ToolMenu->Text = L"ツール(&T)";
			this->ToolMenu->Click += gcnew System::EventHandler(this, &MyForm::ToolMenu_Click);
			// 
			// ToolMenu_Reverse
			// 
			this->ToolMenu_Reverse->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ToolMenu_Reverse_TopBottom,
					this->ToolMenu_Reverse_LeftRight
			});
			this->ToolMenu_Reverse->Name = L"ToolMenu_Reverse";
			this->ToolMenu_Reverse->Size = System::Drawing::Size(180, 22);
			this->ToolMenu_Reverse->Text = L"反転";
			this->ToolMenu_Reverse->Click += gcnew System::EventHandler(this, &MyForm::ToolMenu_Reverse_Click);
			// 
			// ToolMenu_Reverse_TopBottom
			// 
			this->ToolMenu_Reverse_TopBottom->Name = L"ToolMenu_Reverse_TopBottom";
			this->ToolMenu_Reverse_TopBottom->Size = System::Drawing::Size(124, 22);
			this->ToolMenu_Reverse_TopBottom->Text = L"上下反転";
			this->ToolMenu_Reverse_TopBottom->Click += gcnew System::EventHandler(this, &MyForm::ToolMenu_Reverse_TopBottom_Click);
			// 
			// ToolMenu_Reverse_LeftRight
			// 
			this->ToolMenu_Reverse_LeftRight->Name = L"ToolMenu_Reverse_LeftRight";
			this->ToolMenu_Reverse_LeftRight->Size = System::Drawing::Size(124, 22);
			this->ToolMenu_Reverse_LeftRight->Text = L"左右反転";
			this->ToolMenu_Reverse_LeftRight->Click += gcnew System::EventHandler(this, &MyForm::ToolMenu_Reverse_LeftRight_Click);
			// 
			// ToolMenu_Resize
			// 
			this->ToolMenu_Resize->Name = L"ToolMenu_Resize";
			this->ToolMenu_Resize->Size = System::Drawing::Size(180, 22);
			this->ToolMenu_Resize->Text = L"リサイズ";
			this->ToolMenu_Resize->Click += gcnew System::EventHandler(this, &MyForm::ToolMenu_Resize_Click);
			// 
			// ToolMenu_Rotate
			// 
			this->ToolMenu_Rotate->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ToolMenuRotate_90,
					this->ToolMenu_Rotate_270
			});
			this->ToolMenu_Rotate->Name = L"ToolMenu_Rotate";
			this->ToolMenu_Rotate->Size = System::Drawing::Size(180, 22);
			this->ToolMenu_Rotate->Text = L"回転";
			this->ToolMenu_Rotate->Click += gcnew System::EventHandler(this, &MyForm::ToolMenu_Rotate_Click);
			// 
			// ToolMenuRotate_90
			// 
			this->ToolMenuRotate_90->Name = L"ToolMenuRotate_90";
			this->ToolMenuRotate_90->Size = System::Drawing::Size(127, 22);
			this->ToolMenuRotate_90->Text = L"90°回転";
			this->ToolMenuRotate_90->Click += gcnew System::EventHandler(this, &MyForm::ToolMenuRotate_90_Click);
			// 
			// ToolMenu_Rotate_270
			// 
			this->ToolMenu_Rotate_270->Name = L"ToolMenu_Rotate_270";
			this->ToolMenu_Rotate_270->Size = System::Drawing::Size(127, 22);
			this->ToolMenu_Rotate_270->Text = L"270°回転";
			this->ToolMenu_Rotate_270->Click += gcnew System::EventHandler(this, &MyForm::ToolMenu_Rotate_270_Click);
			// 
			// ToolMenu_Insert
			// 
			this->ToolMenu_Insert->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ToolMenuInsert_circle,
					this->ToolMenuInsert_rectangle, this->ToolMenuInsert_line, this->ToolMenuInsert_text
			});
			this->ToolMenu_Insert->Name = L"ToolMenu_Insert";
			this->ToolMenu_Insert->Size = System::Drawing::Size(180, 22);
			this->ToolMenu_Insert->Text = L"挿入";
			this->ToolMenu_Insert->Click += gcnew System::EventHandler(this, &MyForm::ToolMenu_Insert_Click);
			// 
			// ToolMenuInsert_circle
			// 
			this->ToolMenuInsert_circle->Name = L"ToolMenuInsert_circle";
			this->ToolMenuInsert_circle->Size = System::Drawing::Size(180, 22);
			this->ToolMenuInsert_circle->Text = L"円";
			this->ToolMenuInsert_circle->Click += gcnew System::EventHandler(this, &MyForm::ToolMenuInsert_circle_Click);
			// 
			// ToolMenuInsert_rectangle
			// 
			this->ToolMenuInsert_rectangle->Name = L"ToolMenuInsert_rectangle";
			this->ToolMenuInsert_rectangle->Size = System::Drawing::Size(180, 22);
			this->ToolMenuInsert_rectangle->Text = L"四角";
			this->ToolMenuInsert_rectangle->Click += gcnew System::EventHandler(this, &MyForm::ToolMenuInsert_rectangle_Click);
			// 
			// ToolMenuInsert_line
			// 
			this->ToolMenuInsert_line->Name = L"ToolMenuInsert_line";
			this->ToolMenuInsert_line->Size = System::Drawing::Size(180, 22);
			this->ToolMenuInsert_line->Text = L"線";
			this->ToolMenuInsert_line->Click += gcnew System::EventHandler(this, &MyForm::ToolMenuInsert_line_Click);
			// 
			// ToolMenuInsert_text
			// 
			this->ToolMenuInsert_text->Name = L"ToolMenuInsert_text";
			this->ToolMenuInsert_text->Size = System::Drawing::Size(180, 22);
			this->ToolMenuInsert_text->Text = L"文字";
			this->ToolMenuInsert_text->Click += gcnew System::EventHandler(this, &MyForm::ToolMenuInsert_text_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(32, 41);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(419, 242);
			this->panel1->TabIndex = 1;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(45, 14);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(319, 206);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(511, 346);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		/*----- private function ------*/
		private: System::Void windowSize(PictureBox^  pbox, int col, int row) {
		this->ClientSize = Drawing::Size(col, row + menuStrip1->Height);
	}

		/*=== イベントプロシージャ ===*/
		/*----- [ファイル(F)] ------*/
		private: System::Void FileMenu_Click(System::Object^  sender, System::EventArgs^  e) {}
		/* [ファイル(F)>開く(O) ] */
		private: System::Void FileMenu_Open_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ファイル(F)>名前を付けて保存(A) ] */
		private: System::Void FileMenu_SaveAs_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ファイル(F)>初期状態に戻す(I) ] */
		private: System::Void FileMenu_Initialize_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ファイル(F)>閉じる(C) ] */
		private: System::Void FileMenu_Close_Click(System::Object^  sender, System::EventArgs^  e);

		/*----- [ツール(T)] ------*/
		private: System::Void ToolMenu_Click(System::Object^  sender, System::EventArgs^  e) {}
		/* [ツール(T)>反転] */
		private: System::Void ToolMenu_Reverse_Click(System::Object^  sender, System::EventArgs^  e) {}
		/* [ツール(T)>反転>上下反転] */
		private: System::Void ToolMenu_Reverse_TopBottom_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ツール(T)>反転>左右反転] */
		private: System::Void ToolMenu_Reverse_LeftRight_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ツール(T)>リサイズ] */
		private: System::Void ToolMenu_Resize_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ツール(T)>回転] */
		private: System::Void ToolMenu_Rotate_Click(System::Object^  sender, System::EventArgs^  e) {
	}
		/* [ツール(T)>回転>90°回転] */
		private: System::Void ToolMenuRotate_90_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ツール(T)>回転>270°回転] */
		private: System::Void ToolMenu_Rotate_270_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ツール(T)>挿入] */
		private: System::Void ToolMenu_Insert_Click(System::Object^  sender, System::EventArgs^  e) {
		}
		/* [ツール(T)>挿入>円] */
		private: System::Void ToolMenuInsert_circle_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ツール(T)>挿入>四角] */
		private: System::Void ToolMenuInsert_rectangle_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ツール(T)>挿入>線] */
		private: System::Void ToolMenuInsert_line_Click(System::Object^  sender, System::EventArgs^  e);
		/* [ツール(T)>挿入>文字] */
		private: System::Void ToolMenuInsert_text_Click(System::Object^  sender, System::EventArgs^  e);

		/*----- マウス操作 ------*/
		private: System::Void myMouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			if (mEdit.empty())		return;
			if (mInsertType == INSERT_TYPE_NONE)	return;

			/*左クリックのみ有効*/
			if (e->Button != System::Windows::Forms::MouseButtons::Left)	return;

			/*マウス操作/マウスを離した際のイベントハンドラ登録*/
			Control^ control = dynamic_cast<Control^>(sender);
			control->MouseMove += gcnew MouseEventHandler(this, &MyForm::myMouseMove);
			control->MouseUp += gcnew MouseEventHandler(this, &MyForm::myMouseUp);

			/*マウスクリックした始点を記憶*/
			mStartPoint = cv::Point(e->X, e->Y);
		}
		private: System::Void myMouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		}
		private: System::Void myMouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			mat2bmp myObj;

			if (mEdit.empty())		return;
			if (mInsertType == INSERT_TYPE_NONE)	return;

			/*左クリックのみ有効*/
			if (e->Button != System::Windows::Forms::MouseButtons::Left)	return;

			/* マウスを離した座標を記憶し、始点からの高さ/幅を計算 */
			cv::Point endPoint = cv::Point(e->X, e->Y);
			int width = endPoint.x - mStartPoint.x;
			int height = endPoint.y- mStartPoint.y;

			switch (mInsertType) {
			  case INSERT_TYPE_CIRCLE:
				{
				  /*円の場合は中心と半径を計算*/
				  cv::Point center = cv::Point((mStartPoint.x + (width / 2)), (mStartPoint.y + (height / 2)));
				  int radius = (width < height) ? width / 2 : height / 2;

				  /*円を描画*/
				  cv::circle(mEdit,
							 center,			/*中心*/
							 radius,			/*半径*/
							 Scalar(0,0,255),	/*色*/
							 5,					/*線の太さ*/
							 LINE_8);			/*線の種類*/
			    }
				break;
			  case INSERT_TYPE_RECTANGLE:
			    {
				  cv::rectangle(mEdit,
								cv::Point(mStartPoint.x, mStartPoint.y),	/*始点*/
								cv::Point(endPoint.x, endPoint.y),			/*終点*/
								Scalar(0, 0, 255),							/*色*/
								5,											/*線の太さ*/
								LINE_8);									/*線の種類*/
				}
				break;
			  case INSERT_TYPE_LINE:
			    {
				  cv::line(mEdit,
						   cv::Point(mStartPoint.x, mStartPoint.y),	/*始点*/
						   cv::Point(endPoint.x, endPoint.y),		/*終点*/
						   Scalar(0, 0, 255),						/*色*/
						   5,										/*線の太さ*/
						   LINE_8);									/*線の種類*/
			    }
				break;
			  case INSERT_TYPE_TEXT:
			    {
				  cv::putText(mEdit,
					  "TEST",											/*表示するテキスト*/
					  cv::Point(mStartPoint.x, mStartPoint.y),			/*テキストの左上隅の座標*/
					  FONT_HERSHEY_TRIPLEX,								/*フォントの種類*/
					  0.8,												/*フォントのスケール*/
					  Scalar(0, 0, 255),								/*フォントの色*/
					  2,												/*フォントの太さ*/
					  LINE_8,											/*線の種類*/
					  false						);						/*左下起点(falseは左上)*/
			    }
				break;
			  default:
				break;
			}

			pictureBox1->Image = myObj.mat2mbp(mEdit, &mEdit);

			/*イベントハンドラを解除*/
			Control^ control = dynamic_cast<Control^>(sender);
			control->MouseMove -= gcnew MouseEventHandler(this, &MyForm::myMouseMove);
			control->MouseUp -= gcnew MouseEventHandler(this, &MyForm::myMouseUp);
		}
};
}