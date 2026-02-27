//
// Created by c4ner on 2/10/2026.
//
#include <iostream>
#include <conio.h>
#include <cstring>
#include <limits>
using namespace std;

void seqyentialSearch(string& T, string& P) {
     unsigned int steps = 0;
     size_t n = T.length(); //поверт. кількість символів в рядку
     size_t m = P.length();
    bool found = false;
    for (int S = 0; S <= n-m; S++) {
        int j = 0;
        steps++;
        while (j < m && P[j] == T[S+j]) {
            j++;
            steps++;
        }
        if (j == m) {
            cout << "Зразок знайдено на позиції S = " << S << endl;
            cout << "Кроків знадобилось: " << steps << "  ENTER" << endl;
            found = true;

            _getch();
        }
    }
    if (!found) {
        cout << "Нічого не було знайдено!" << endl;
        cout << "Кроків знадобилось: " << steps << "  ENTER" << endl;
        _getch();
    }
 }
//---------------------------------------------------------------
void KMPSearch(string& text, string& pattern) {
    int n = static_cast<int>(text.length());
    int m = static_cast<int>(pattern.length());
    unsigned int steps = 0;

    if (m == 0) {
        return; //захист якшо порожньо
    }
    //будуємо префікс-функцію
    int *f = new int[m]; //еслі фейл на якомусь індексі, стрибай одразу на Х і не починай спочатку.
    f[0] = 0;
    int j = 0;

    for (int i = 1;  i < m; i++) {
        steps++;
        while (j > 0 && pattern[i] != pattern[j]) {
            steps++;
            j = f[j - 1]; //назад откат до нашої шпори
        }
            if (pattern[i] == pattern[j]) {
                j++;
            }
            f[i] = j;
        }

    //етап 2 це пошук
    j = 0; //кількість збігу, ОБОВЯЗКОВО СКИНУТИ НАНОВО
    bool found = false;

    for (int i = 0; i < n; i++) {
        steps++;
        while (j > 0 && text[i] != pattern[j]) {
            steps++;
            j = f[j - 1]; //знову назад по шпаргалкє
        }
            if (text[i] == pattern[j]) {
                j++; //символ співпадає ідем далі
            }
            if (j == m) {
                cout << "Знайдено на позиції: " << (i-m+1) << endl;
                found = true;
                j = f[j-1]; //шукаємо далі
            }
        }
        delete[] f;
    if (!found) {
        cout << "Нічого не було знайдено!" << endl;
        return;
    }
    cout << "Всього кроків " << steps << endl;
    }

//--------------------------------------------------------------------------------
//функція що допомогає та робить таблицю для зсувів
//для кожної букви записано де вона востаннє зустрінеця
void TablicaBM(string& str, int m, int badchar[256], unsigned int &steps) {
    //спочатку букв ніде нема
    for (int i = 0; i < 256; i++) { //256 тому шо 256 символів це алфавіт компа. всього існує 256 символів.
        badchar[i] = -1;
        //тут ми надаємо, наприклад букві З значення -1.
        //тому що наприклад у слові DOG нема Z
    }
    //наші реал поозиціі
    for (int i = 0; i < m; i++) {
        badchar[static_cast<int>(str[i])] = i;
        steps++;
    }
}
void BMSearch(string& text, string& pattern) {
    int n = static_cast<int>(text.length());
    int m = static_cast<int>(pattern.length());
    unsigned int steps = 0;
    bool found = false;
    if (m == 0) {
        return;
    }
    int badchar[256];
    //табла символів НЕ ТАКИХ:
    TablicaBM(pattern, m, badchar, steps);
    int s = 0; //зсув шаблону відносно початку/SHIFT!!!
    while (s <= (n-m)) {
        int j = m-1;
        steps++;
        while (j >= 0 && pattern[j] == text[s+j]) {
            j--;
            steps++;
        }
        if (j<0) {
            cout << "БМ: Знайдено на позиції: " << s << endl;
            found = true;

            //ідемо далі
            if (s+m<n) {
                s += m - badchar[static_cast<int>(text[s+m])];
            }
            else {
                s += 1;
            }
        }
        else {
            //НЕМАЄ співпадіння!
            //йотий - індекс паганої букви
            //текст (с+йот) це сама погана буква
            //бадчар - ДЕ ця буква у шаблоні
            //макс потрібен шоб назад не йти
            s += max(1, j-badchar[(static_cast<int>(text[s+j]))]);
        }
    }
    if (!found) {
        cout << "БМ: Нічого не було знайдено!! " << endl;
    }
    cout << "БМ: Всього кроків: " << steps << endl;
}

int main() {
    char varik = 0;
    do {
        cout << "Програма реалізує пошук підрядків у рядках." << endl;
        cout << "Оберіть алгоритм пошуку яким хочете скористатись:" <<endl;
        cout << "1) Алгоритм послідовного пошуку" << endl;
        cout << "2) Алгоритм Кнута-Морріса-Пратта" << endl;
        cout << "3) Алгоритм Бойєра-Мура" << endl;

        char var = 6; //NOLINT
        do {
            var = _getch(); //NOLINT
            if (var != '1' && var != '2' && var != '3') {
                cout << "Ви вводите некорректні значення. Спробуйте ще раз." << endl;
            }
        }while (var != '1' && var != '2' && var != '3');

        string T = "ankakbbykbnnakapkp";
        string P = "kbbykbbybk";
        cout << "\nДано текст: " << T << endl;
        cout << "Зразок: " << P << endl;
        char swetche_vibor = 0;
        switch (var) {
            case '1':
                seqyentialSearch(T, P);
                cout << "Хочете спробувати ввести свої букви і знайти їх в данних? 0-так/1-ні "<< endl;
                do {
                    swetche_vibor = _getch(); //NOLINT
                    if (swetche_vibor == '0') {
                        string P_Pol;
                        cout << "Введіть свої літери" << endl;
                        cin >> P_Pol;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        seqyentialSearch(T, P_Pol);
                        cout << "Натисніть 0 щоб продовжити. 1 щоб вийти з ПОСЛІДОВНОГО пошуку." << endl;
                    }
                }while (swetche_vibor != '1');
                break;
            case '2':
                KMPSearch(T, P);
                cout << "Хочете спробувати ввести свої букви і знайти їх в данних? 0-так/1-ні "<< endl;
                do {
                    swetche_vibor = _getch(); //NOLINT
                    if (swetche_vibor == '0') {
                        string P_Pol;
                        cout << "Введіть свої літери" << endl;
                        cin >> P_Pol;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        KMPSearch(T, P_Pol);
                        cout << "Натисніть 0 щоб продовжити. 1 щоб вийти з КМП пошуку." << endl;
                    }
                }while (swetche_vibor != '1');
                break;
            case '3':
                BMSearch(T,P);
                cout << "Хочете спробувати ввести свої букви і знайти їх в данних? 0-так/1-ні "<< endl;
                do {
                    swetche_vibor = _getch(); //NOLINT
                    if (swetche_vibor == '0') {
                        string P_Pol;
                        cout << "Введіть свої літери" << endl;
                        cin >> P_Pol;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        BMSearch(T, P_Pol);
                        cout << "Натисніть 0 щоб продовжити. 1 щоб вийти з БМ пошуку." << endl;
                    }
                }while (swetche_vibor != '1');

                break;
            default:
                cerr << "Виникла помилка." << endl;
                exit(1);
                break;
        }
        cout << "Чи хочете ви повернутись в меню? 0 - так/1 - ні" << endl;
        varik = _getch(); //NOLINT
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }while (varik != '1');
    return 0;
}