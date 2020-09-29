#include <iostream>
using namespace std;

class HillCipher
{
private:
    // operasi mod
    int mod(int a, int b)
    {
        int c = a % b;
        return (c < 0) ? c + b : c;
    }
    //menghitung gcd
    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }

    // menghitung inverse b  mod a
    int calculateInverse(int a, int b)
    {
        int xTemp = 1, x = 0;
        int yTemp = 0, y = 1;
        int hasilBagi, sisa, temp;
        int n = a;
        while (b != 0)
        {
            hasilBagi = a / b; //hasil bagi
            sisa = a % b;      //sisa
            temp = x;
            x = xTemp - hasilBagi * x;
            xTemp = temp;
            temp = y;
            y = yTemp - hasilBagi * y;
            yTemp = temp;
            a = b;
            b = sisa;
        }
        int inverse = mod(yTemp, n);
        return inverse;
    }

public:
    int key[2][2];
    bool isOdd;
    // mengambil input key dari user
    void inputKey()
    {
        cout << "Masukkan 4 elemen kunci matriks 2 x 2 dengan urutan :\n";
        cout << "1 3 \n2 4\n";
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << "Key : ";
                cin >> key[i][j];
            }
        }
    }
    //mengecek kevalidan key
    bool isValid(int a[2][2])
    {
        int det = (a[0][0] * a[1][1]) - (a[1][0] * a[0][1]);
        det = mod(det, 26);

        //jika determinan koprima dengan mod 26 maka
        //matriks invertible jika di mod 26
        // sehingga key valid
        return (gcd(det, 26) == 1) ? true : false;
    }
    //mengambil message
    string getMessage()
    {
        string message;
        isOdd = false;
        cout << "Masukkan Message : ";
        cin >> message;

        // Jika message lower case
        for (int i = 0; i < message.length(); i++)
        {
            message[i] = toupper(message[i]);
        }
        if (message.length() % 2 != 0)
        {
            isOdd = true;
            message += "A";
        }
        return message;
    }
    // fungsi enkripsi
    void encrypt(string message)
    {
        // print key matrix
        cout << "Key dari matrix : \n";
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                cout << key[i][j] << " ";
            cout << endl;
        }
        string cipherText = "";
        int row = message.length() / 2;
        //int matrix untuk message
        int message2D[row][2];
        int p = 0;
        do
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    message2D[i][j] = message[p] - 'A';
                    p++;
                }
            }
        } while (p < message.length());

        //pengecekan matrix
        cout << "Matriks dari message tadi : " << endl;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << message2D[i][j] << " ";
            }
            cout << endl;
        }
        cout << "\n";
        //dalam bentuk alfabet
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << (char)(message2D[i][j] + 'A') << " ";
            }
            cout << endl;
        }
        //mengalikan message matrix dengan key matrix
        int m[row][2];
        int i, j, k, hasil = 0;
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < 2; j++)
            {
                for (k = 0; k < 2; k++)
                {
                    hasil = hasil + message2D[i][k] * key[k][j];
                }
                m[i][j] = mod(hasil, 26);
                hasil = 0;
            }
        }

        cout << "Setelah dienkripsi hasilnya adalah : \n";
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < 2; j++)
                cout << m[i][j] << " ";
            cout << "\n";
        }
        //generating cipherText
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                char c = toupper(m[i][j] + 'A');
                cipherText.push_back(c);
            }
        }
        if (isOdd)
        {
            cout << "\nKarena input message memiliki jumlah huruf ganjil maka diakhir message ditambah dengan huruf 'A'\n";
        }
        cout << "Plaintext : " << message << endl;
        cout << "CipherText : " << cipherText;
    }
    // fungsi dekripsi
    void decrypt(string message)
    {
        string plainText = "";
        int row = message.length() / 2;
        //int matrix for message
        int message2D[row][2];
        int p = 0;
        do
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    message2D[i][j] = message[p] - 'A';
                    p++;
                }
            }
        } while (p < message.length());
        //testing matrix
        cout << "Matrix dari message diatas :" << endl;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << message2D[i][j] << " ";
            }
            cout << endl;
        }
        // dalam bentuk alfabet
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << (char)(message2D[i][j] + 'A') << " ";
            }
            cout << endl;
        }
        //menghitung determinan
        int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
        det = mod(det, 26);
        cout << "Determinan : " << det << "\t";
        //menghitung 1/det mod 26
        int satuperDeterminan = calculateInverse(26, det);
        cout << "1/determinan : " << satuperDeterminan << "\n";
        //menghitung inverse key

        int inverseKey[row][2];
        inverseKey[0][0] = mod(satuperDeterminan * key[1][1], 26);
        inverseKey[1][1] = mod(satuperDeterminan * key[0][0], 26);
        inverseKey[0][1] = mod(satuperDeterminan * -1 * key[0][1], 26);
        inverseKey[1][0] = mod(satuperDeterminan * -1 * key[1][0], 26);
        cout << "Inverse Matrix Key : \n";
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                cout << inverseKey[i][j] << " ";
            cout << endl;
        }
        int m[row][2];
        int i, j, k, hasil = 0;
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < 2; j++)
            {
                for (k = 0; k < 2; k++)
                {
                    hasil = hasil + message2D[i][k] * inverseKey[k][j];
                }
                m[i][j] = mod(hasil, 26);
                hasil = 0;
            }
        }
        cout << "Hasil Dekripsi \n";
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < 2; j++)
                cout << m[i][j] << " ";
            cout << "\n";
        }
        //print plaintText
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                char c = toupper(m[i][j] + 'A');
                plainText.push_back(c);
            }
        }
        cout << "Cipher Text : " << message << endl;
        cout << "Plain Text : " << plainText;
    }
};

int main()
{
    HillCipher hCipher;
    string message;
    int choice;
    char loop = 'y';
    while (loop == 'y' || loop == 'Y')
    {
        system("CLS");
        cout << "HILL CIPHER 2x2" << endl
             << endl;
        cout << "1. Enkripsi\n";
        cout << "2. Dekripsi\n";
        cout << "3. Exit\n";
        cout << "Masukkan pilihan : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            hCipher.inputKey();
            if (hCipher.isValid(hCipher.key))
            {
                cout << "Key yang dimasukkan valid\n";
            }
            else
            {
                cout << "Key yang dimasukkan tidak valid, masukkan kembali keynya\n";
                exit(0);
            }
            message = hCipher.getMessage();
            hCipher.encrypt(message);
            break;
        case 2:
            hCipher.inputKey();
            if (hCipher.isValid(hCipher.key))
            {
                cout << "Key yang dimasukkan valid\n";
            }
            else
            {
                cout << "Key yang dimasukkan tidak valid, masukkan kembali keynya\n";
                exit(0);
            }
            message = hCipher.getMessage();
            hCipher.decrypt(message);
            break;
        case 3:
            exit(0);
        default:
            cout << "Pilihan salah" << endl;
        }
        cout << "\n\nPencet y jika ingin melanjutkan program : ";
        cin >> loop;
    }
    return 0;
}
