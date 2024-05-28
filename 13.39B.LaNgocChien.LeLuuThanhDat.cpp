#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

class NhanVien 
{
public:
    string maNV;
    string tenNV;
    string chucvu;
    float hesoLuong;
    float luong;
    float phucapchucvu;
    float thuclinh;

    float getPhuCap(string chucvu) 
    {
        if (chucvu == "GD")
            return 5000000;
        if (chucvu == "TP")
            return 4000000;
        if (chucvu == "NV")
            return 1000000;
        return 0;
    }

    void nhap1NV() 
    {
        cout << "Nhap vao ma nhan vien: ";
        getline(cin, maNV);
        cout << "Nhap vao ten nhan vien: ";
        getline(cin, tenNV);

        do {
            cout << "Nhap chuc vu (GD, TP, NV): ";
            getline(cin, chucvu);
        } while (!(chucvu == "GD" || chucvu == "TP" || chucvu == "NV"));

        do {
            cout << "Nhap vao he so luong: ";
            cin >> hesoLuong;
        } while (hesoLuong <= 0);
        luong = hesoLuong * 1490000;
        phucapchucvu = getPhuCap(chucvu);
        thuclinh = luong + phucapchucvu;
        cin.ignore();
    }
};

void nhap05NV(NhanVien *ds, int &n) 
{
    do {
        cout << "Nhap vao so luong nhan vien: ";
        cin >> n;
    } while (n < 1 || n > 100);
    cin.ignore();

    for (int i = 0; i < n; i++) 
    {
        cout << "\tNHAP THONG TIN CUA NHAN VIEN THU " << i + 1 << endl;
        ds[i].nhap1NV(); 
    }
}


// xuat nhan vien
void xuatNhanVien(NhanVien x)
 {
    cout << setw(15) << x.maNV;
    cout << setw(23) << x.tenNV;
    cout << setw(12) << x.chucvu;
    cout << setw(15) << x.hesoLuong;
    cout << setw(15) << x.luong;
    cout << setw(15) << x.phucapchucvu;
    cout << setw(15) << x.thuclinh << endl;
}

// xuat danh sach nhan vien 
void xuatDSNhanVien(NhanVien ds[], int n) 
{
    cout << setw(15) << "Ma NV";
    cout << setw(23) << "Ho va Ten";
    cout << setw(12) << "Chuc Vu";
    cout << setw(15) << "He so Luong";
    cout << setw(15) << "Luong";
    cout << setw(15) << "Phu cap CV";
    cout << setw(15) << "Thuc linh" << endl;
    for (int i = 0; i < n; i++) {
        xuatNhanVien(ds[i]);
    }
}

// xuat danh sach nhan vien TP
void xuatDSNhanVienTP(NhanVien ds[], int n)
 {
    cout << setw(15) << "Ma NV";
    cout << setw(23) << "Ho va Ten";
    cout << setw(12) << "Chuc Vu";
    cout << setw(15) << "He so Luong";
    cout << setw(15) << "Luong";
    cout << setw(15) << "Phu cap CV";
    cout << setw(15) << "Thuc linh" << endl;
    for (int i = 0; i < n; i++) {
        if (ds[i].chucvu == "TP") {
            xuatNhanVien(ds[i]);
        }
    }
}

// sap xep theo thuc linh nhan vien
void sapxeptheothuclinh(NhanVien *ds, int n)
 {
    int i, j;
    NhanVien x;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (ds[i].thuclinh < ds[j].thuclinh) {
                x = ds[i];
                ds[i] = ds[j];
                ds[j] = x;
            }
        }
    }
}

// them nhan vien
void themNhanVien(NhanVien *ds, int &n)
{
    cout << "\tNHAP NHAN VIEN MUON THEM VAO\n";
    NhanVien x;
    x.nhap1NV();
    ds[n] = x;
    n++;
    sapxeptheothuclinh(ds, n);
    cout << "DANH SACH SAU KHI THEM VAO\n";
    xuatDSNhanVien(ds, n);
}


// xoa khoi danh sach
void xoakhoidanhsach(NhanVien *ds, int &n)
 {
    float hs_luong;
    cout << "Nhap he so luong: ";
    cin >> hs_luong;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        if (ds[i].hesoLuong < hs_luong) {
            for (int j = i; j < n - 1; j++) {
                ds[j] = ds[j + 1];
            }
            n--;
            i--;
        }
    }
    cout << "DANH SACH NHAN VIEN SAU KHI XOA\n";
    xuatDSNhanVien(ds, n);
}

// luu danh sach nhan vien
void savedanhsachNhanVien(NhanVien ds[], int n) 
{
    ofstream fo("nv1.txt");
    fo << n << endl;
    for (int i = 0; i < n; i++) {
        fo << ds[i].maNV << endl;
        fo << ds[i].tenNV << endl;
        fo << ds[i].chucvu << endl;
        fo << ds[i].hesoLuong << endl;
        fo << ds[i].luong << endl;
        fo << ds[i].phucapchucvu << endl;
        fo << ds[i].thuclinh << endl;
        fo << "-----------------\n";
    }
    fo.close();
}

// doc danh sach nhan vien
void docdanhsach(NhanVien *ds, int &n) 
{
    ifstream fi("nv1.txt");
    string str;
    fi >> n;
    fi.ignore();
    for (int i = 0; i < n; i++) {
        getline(fi, ds[i].maNV);
        getline(fi, ds[i].tenNV);
        getline(fi, ds[i].chucvu);
        fi >> ds[i].hesoLuong;
        fi >> ds[i].luong;
        fi >> ds[i].phucapchucvu;
        fi >> ds[i].thuclinh;
        fi.ignore();
        getline(fi, str); // Doc dong "-----------------"
    }
    fi.close();
}

// xay dung menu chuc nang nhan vien cong ty
void menu()
 {
    cout << "------------------------------MENU-----------------------------|\n";
    cout << "| 1. THOAT                                                     |\n";
    cout << "| 2. NHAP VAO TU BAN PHIM DS NHAN VIEN                         |\n";
    cout << "| 3. TINH LUONG NHAN VIEN                                      |\n";
    cout << "| 4. IN RA MAN HINH DANH SACH NHAN VIEN                        |\n";
    cout << "| 5. SAP XEP THEO GIAM DAN THUC LINH                           |\n";
    cout << "| 6. IN RA MAN HINH DS NV CO CHUC VU LA TP                     |\n";
    cout << "| 7. THEM VAO NHAN VIEN                                        |\n";
    cout << "| 8. XOA NHAN VIEN CO HSL < hs_luong                           |\n";
    cout << "| 9. LUU DSNV RA TEP nv1.txt                                   |\n";
    cout << "|10. DOC DANH SACH NHAN VIEN TU TEP nv1.txt VA IN RA MAN HINH  |\n";
    cout << "----------------------------------------------------------------\n";
    cout << "\tLua chon: ";
}

int main() 
{
    int chon;
    NhanVien ds[100];
    int n = 0;
    cout << setprecision(9);

    while (1)
	 {
        menu();
        cin >> chon;
        cin.ignore();
        switch (chon) 
		{
            case 1: 
			{
                cout << "Ban chon thoat\n";
                return 0;
            }
            case 2:
			{
                nhap05NV(ds, n);
                system("pause");
                break;
            }
            case 3:
		    {
                cout << "DANH SACH NHAN VIEN SAU KHI TINH LUONG\n";
                xuatDSNhanVien(ds, n);
                system("pause");
                break;
            }
            case 4: 
			{
                cout << "\tDANH SACH NHAN VIEN\n";
                xuatDSNhanVien(ds, n);
                system("pause");
                break;
            }
            case 5: 
			{
                sapxeptheothuclinh(ds, n);
                cout << "\tDANH SACH NHAN VIEN SAU KHI SAP XEP\n";
                xuatDSNhanVien(ds, n);
                system("pause");
                break;
            }
            case 6: 
			{
                cout << "\tDANH SACH NHAN VIEN CO CHUC VU LA TP\n";
                xuatDSNhanVienTP(ds, n);
                system("pause");
                break;
            }
            case 7: 
			{
                themNhanVien(ds, n);
                system("pause");
                break;
            }
            case 8: 
			{
                xoakhoidanhsach(ds, n);
                system("pause");
                break;
            }
            case 9: 
			{
                savedanhsachNhanVien(ds, n);
                cout << "LUU THANH CONG\n";
                system("pause");
                break;
            }
            case 10: 
			{
                docdanhsach(ds, n);
                cout << "\tDANH SACH NHAN VIEN DOC TU FILE\n";
                xuatDSNhanVien(ds, n);
                system("pause");
                break;
            }
            default: 
			{
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                system("pause");
                break;
            }
        }
    }
    return 0;
}



