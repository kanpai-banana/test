#include <Windows.h>
#include "MyForm.h"

using namespace Project2;

[STAThreadAttribute]

/**************************/
/* ���C���֐�             */
/**************************/
int main()
{
	MyForm ^fm = gcnew MyForm();
	fm->ShowDialog();
	return 0;
}

/*=== �C�x���g�v���V�[�W�� ===*/
/*----- [�t�@�C��(F)] ---------------------------------------------------------------*/
/**************************/
/* [�t�@�C��(F)>�J��(O) ] */
/**************************/
System::Void MyForm::FileMenu_Open_Click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog ^dlg = gcnew OpenFileDialog;
	dlg->Filter = "jpg�摜�t�@�C��(*.jpg,*.JPG)|*.jpg;*.JPG \
				  |pnģ��(*.png)|*.png;*.PNG"              \
		;

	/*�L�����Z��*/
	if (dlg->ShowDialog() == Windows::Forms::DialogResult::Cancel)	return;

	System::String ^fname = dlg->FileName;
	mat2bmp myObj;

	mSrc = myObj.readFile(fname);
	/*�摜�擾���s*/
	if (mSrc.empty())		return;

	mEdit.release();	/*mEdit��������*/

	this->Text = IO::Path::GetFileName(dlg->FileName);

	pictureBox1->Image = myObj.mat2mbp(mSrc, &mEdit);	/*�J�����摜��mEdit�ɕۑ�*/
	windowSize(pictureBox1, mEdit.cols, mEdit.rows);
}
/***************************************/
/* [�t�@�C��(F)>���O��t���ĕۑ�(A) ] */
/***************************************/
System::Void MyForm::FileMenu_SaveAs_Click(System::Object^  sender, System::EventArgs^  e) {
	if (mEdit.empty())	return;

	SaveFileDialog^ dlg = gcnew SaveFileDialog;
	dlg->Filter = "jpg�摜�t�@�C��(*.jpg,*.JPG)|*.jpg;*.JPG \
				  |pnģ��(*.png)|*.png;*.PNG"              \
		;

	/*�L�����Z��*/
	if (dlg->ShowDialog() == Windows::Forms::DialogResult::Cancel)	return;

	mat2bmp myObj;
	myObj.writeFile(dlg->FileName, &mEdit);
}
/***************************************/
/* [�t�@�C��(F)>������Ԃɖ߂�(I) ]    */
/***************************************/
System::Void MyForm::FileMenu_Initialize_Click(System::Object^  sender, System::EventArgs^  e){
	mat2bmp myObj;
	if (mSrc.empty())	return;

	/*�������񏉊���*/
	mEdit.release();

	pictureBox1->Image = myObj.mat2mbp(mSrc, &mEdit);
	windowSize(pictureBox1, mEdit.cols, mEdit.rows);
}
/***************************************/
/* [�t�@�C��(F)>����(C) ]            */
/***************************************/
System::Void MyForm::FileMenu_Close_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}

/*----- [�c�[��(T)] ---------------------------------------------------------------*/
/***************************************/
/* [�c�[��(T)>���]>�㉺���]]           */
/***************************************/
System::Void MyForm::ToolMenu_Reverse_TopBottom_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp;	/*�ҏW��̉摜���ꎞ�ۑ�����*/
	mat2bmp myObj;
	if (mEdit.empty()) return;

	/* 0 : �㉺���]
	   >0: ���E���]
	   <0: ��������Ŕ��]*/
	flip(mEdit, tmp, 0);

	/*Window�ɕҏW�����摜��\��*/
	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEdit�̏����ŐV�ɍX�V*/
	mEdit = tmp;
}
/***************************************/
/* [�c�[��(T)>���]>���E���]]           */
/***************************************/
System::Void MyForm::ToolMenu_Reverse_LeftRight_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp;	/*�ҏW��̉摜���ꎞ�ۑ�����*/
	mat2bmp myObj;
	if (mEdit.empty()) return;

	/* 0 : �㉺���]
	   >0: ���E���]
	   <0: ��������Ŕ��]*/
	flip(mEdit, tmp, 1);

	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEdit�̏����ŐV�ɍX�V*/
	mEdit = tmp;
}
/***************************************/
/* [�c�[��(T)>���T�C�Y]                */
/***************************************/
System::Void MyForm::ToolMenu_Resize_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp;	/*�ҏW��̉摜���ꎞ�ۑ�����*/
	mat2bmp myObj;
	if (mEdit.empty()) return;

	resize(mEdit, tmp, cv::Size(), 0.5, 0.5);

	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEdit�̏����ŐV�ɍX�V*/
	mEdit = tmp;
}
/***************************************/
/* [�c�[��(T)>��]>90����]]           */
/***************************************/
System::Void MyForm::ToolMenuRotate_90_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp, matrix;
	mat2bmp myObj;
	if (mEdit.empty()) return;

	/*��]�̌��_*/
	Point2f center = Point2f(static_cast<float>(mEdit.cols / 2), static_cast<float>(mEdit.rows / 2));
	/*��]�̊p�x(�����v)*/
	float angle = 270;

	/*�A�t�B���ϊ��s��*/
	matrix = getRotationMatrix2D(center, angle, 1.0);
	/*��]���s*/
	warpAffine(mEdit, tmp, matrix, cv::Size(mEdit.rows, mEdit.cols), INTER_CUBIC);
	destroyAllWindows();

	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEdit�̏����ŐV�ɍX�V*/
	mEdit = tmp;
}
/***************************************/
/* [�c�[��(T)>��]>270����]]          */
/***************************************/
System::Void MyForm::ToolMenu_Rotate_270_Click(System::Object^  sender, System::EventArgs^  e) {
	Mat tmp, matrix;
	mat2bmp myObj;
	if (mEdit.empty()) return;

	/*��]�̌��_*/
	Point2f center = Point2f(static_cast<float>(mEdit.cols / 2), static_cast<float>(mEdit.rows / 2));
	/*��]�̊p�x(�����v)*/
	float angle = 90;

	/*�A�t�B���ϊ��s��*/
	matrix = getRotationMatrix2D(center, angle, 1.0);
	/*��]���s*/
	warpAffine(mEdit, tmp, matrix, cv::Size(mEdit.rows, mEdit.cols), INTER_CUBIC);

	pictureBox1->Image = myObj.mat2mbp(tmp, &tmp);
	windowSize(pictureBox1, tmp.cols, tmp.rows);

	/*mEdit�̏����ŐV�ɍX�V*/
	mEdit = tmp;
}

/***************************************/
/* [�c�[��(T)>�~]                      */
/***************************************/
System::Void MyForm::ToolMenuInsert_circle_Click(System::Object^  sender, System::EventArgs^  e){
	mInsertType = INSERT_TYPE_CIRCLE;
}
/***************************************/
/* [�c�[��(T)>�l�p]                    */
/***************************************/
System::Void MyForm::ToolMenuInsert_rectangle_Click(System::Object^  sender, System::EventArgs^  e) {
	mInsertType = INSERT_TYPE_RECTANGLE;
}
/***************************************/
/* [�c�[��(T)>��]                      */
/***************************************/
System::Void MyForm::ToolMenuInsert_line_Click(System::Object^  sender, System::EventArgs^  e) {
	mInsertType = INSERT_TYPE_LINE;
}
/***************************************/
/* [�c�[��(T)>����]                    */
/***************************************/
System::Void MyForm::ToolMenuInsert_text_Click(System::Object^  sender, System::EventArgs^  e) {
	mInsertType = INSERT_TYPE_TEXT;
}


