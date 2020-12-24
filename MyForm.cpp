#include <Windows.h>
#include "MyForm.h"

using namespace Project2;

[STAThreadAttribute]

/**************************/
/* メイン関数             */
/**************************/
int main()
{
	MyForm ^fm = gcnew MyForm();
	fm->ShowDialog();
	return 0;
}

/*=== イベントプロシージャ ===*/
/*----- [ファイル(F)] ---------------------------------------------------------------*/
/**************************/
/* [ファイル(F)>開く(O) ] */
/**************************/
System::Void MyForm::FileMenu_Open_Click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog ^dlg = gcnew OpenFileDialog;
	dlg->Filter = "jpg画像ファイル(*.jpg,*.JPG)|*.jpg;*.JPG \
				  |pngﾌｧｲﾙ(*.png)|*.png;*.PNG"              \
		;

	/*キャンセル*/
	if (dlg->ShowDialog() == Windows::Forms::DialogResult::Cancel)	return;

	System::String ^fname = dlg->FileName;
	mat2bmp myObj;

	mSrc = myObj.readFile(fname);
	/*画像取得失敗*/
	if (mSrc.empty())		return;

	mEdit.release();	/*mEditを初期化*/

	this->Text = IO::Path::GetFileName(dlg->FileName);

	pictureBox1->Image = myObj.mat2mbp(mSrc, &mEdit);	/*開いた画像をmEditに保存*/
	windowSize(pictureBox1, mEdit.cols, mEdit.rows);
}
/***************************************/
/* [ファイル(F)>名前を付けて保存(A) ] */
/***************************************/
System::Void MyForm::FileMenu_SaveAs_Click(System::Object^  sender, System::EventArgs^  e) {
	if (mEdit.empty())	return;

	SaveFileDialog^ dlg = gcnew SaveFileDialog;
	dlg->Filter = "jpg画像ファイル(*.jpg,*.JPG)|*.jpg;*.JPG \
				  |pngﾌｧｲﾙ(*.png)|*.png;*.PNG"              \
		;

	/*キャンセル*/
	if (dlg->ShowDialog() == Windows::Forms::DialogResult::Cancel)	return;

	mat2bmp myObj;
	myObj.writeFile(dlg->FileName, &mEdit);
}
/***************************************/
/* [ファイル(F)>初期状態に戻す(I) ]    */
/***************************************/
System::Void MyForm::FileMenu_Initialize_Click(System::Object^  sender, System::EventArgs^  e){
	mat2bmp myObj;
	if (mSrc.empty())	return;

	/*いったん初期化*/
	mEdit.release();

	pictureBox1->Image = myObj.mat2mbp(mSrc, &mEdit);
	windowSize(pictureBox1, mEdit.cols, mEdit.rows);
}
/***************************************/
/* [ファイル(F)>閉じる(C) ]            */
/***************************************/
System::Void MyForm::FileMenu_Close_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}

/*----- [ツール(T)] ---------------------------------------------------------------*/
/***************************************/
/* [ツール(T)>反転>上下反転]           */
/***************************************/
System::Void MyForm::ToolMenu_Reverse_TopBottom_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp;	/*編集後の画像を一時保存する*/
	mat2bmp myObj;
	if (mEdit.empty()) return;

	/* 0 : 上下反転
	   >0: 左右反転
	   <0: 両軸周りで反転*/
	flip(mEdit, tmp, 0);

	/*Windowに編集した画像を表示*/
	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEditの情報を最新に更新*/
	mEdit = tmp;
}
/***************************************/
/* [ツール(T)>反転>左右反転]           */
/***************************************/
System::Void MyForm::ToolMenu_Reverse_LeftRight_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp;	/*編集後の画像を一時保存する*/
	mat2bmp myObj;
	if (mEdit.empty()) return;

	/* 0 : 上下反転
	   >0: 左右反転
	   <0: 両軸周りで反転*/
	flip(mEdit, tmp, 1);

	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEditの情報を最新に更新*/
	mEdit = tmp;
}
/***************************************/
/* [ツール(T)>リサイズ]                */
/***************************************/
System::Void MyForm::ToolMenu_Resize_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp;	/*編集後の画像を一時保存する*/
	mat2bmp myObj;
	if (mEdit.empty()) return;

	resize(mEdit, tmp, cv::Size(), 0.5, 0.5);

	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEditの情報を最新に更新*/
	mEdit = tmp;
}
/***************************************/
/* [ツール(T)>回転>90°回転]           */
/***************************************/
System::Void MyForm::ToolMenuRotate_90_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp, matrix;
	mat2bmp myObj;
	if (mEdit.empty()) return;

	/*回転の原点*/
	Point2f center = Point2f(static_cast<float>(mEdit.cols / 2), static_cast<float>(mEdit.rows / 2));
	/*回転の角度(反時計)*/
	float angle = 270;

	/*アフィン変換行列*/
	matrix = getRotationMatrix2D(center, angle, 1.0);
	/*回転実行*/
	warpAffine(mEdit, tmp, matrix, cv::Size(mEdit.rows, mEdit.cols), INTER_CUBIC);
	destroyAllWindows();

	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEditの情報を最新に更新*/
	mEdit = tmp;
}
/***************************************/
/* [ツール(T)>回転>270°回転]          */
/***************************************/
System::Void MyForm::ToolMenu_Rotate_270_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp, matrix;
	mat2bmp myObj;
	if (mEdit.empty()) return;

	/*回転の原点*/
	Point2f center = Point2f(static_cast<float>(mEdit.cols / 2), static_cast<float>(mEdit.rows / 2));
	/*回転の角度(反時計)*/
	float angle = 90;

	/*アフィン変換行列*/
	matrix = getRotationMatrix2D(center, angle, 1.0);
	/*回転実行*/
	warpAffine(mEdit, tmp, matrix, cv::Size(mEdit.rows, mEdit.cols), INTER_CUBIC);

	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEditの情報を最新に更新*/
	mEdit = tmp;
}

/***************************************/
/* [ツール(T)>円]                      */
/***************************************/
System::Void MyForm::ToolMenuInsert_circle_Click(System::Object^  sender, System::EventArgs^  e){
	mInsertType = INSERT_TYPE_CIRCLE;
}
/***************************************/
/* [ツール(T)>四角]                    */
/***************************************/
System::Void MyForm::ToolMenuInsert_rectangle_Click(System::Object^  sender, System::EventArgs^  e) {
	mInsertType = INSERT_TYPE_RECTANGLE;
}
/***************************************/
/* [ツール(T)>線]                      */
/***************************************/
System::Void MyForm::ToolMenuInsert_line_Click(System::Object^  sender, System::EventArgs^  e) {
	mInsertType = INSERT_TYPE_LINE;
}
/***************************************/
/* [ツール(T)>文字]                    */
/***************************************/
System::Void MyForm::ToolMenuInsert_text_Click(System::Object^  sender, System::EventArgs^  e) {
	mInsertType = INSERT_TYPE_TEXT;
}


