#include <iostream>
#include <limits> // For input validation
using namespace std;

// Fatura kesim dönemleri (Billing cycle days)
const int BC1 = 22;
const int BC2 = 26;
const int BC3 = -1; // Indicates the last day of the month
const int BC4 = 9;

// A ve B tarifelerinin ücretleri (Tariff rates for A and B)
int a_tarife_ucreti;
int b_tarife_ucreti;

// A ve B tarifelerinin süresi (Duration for A and B tariffs)
int a_tarife_suresi;
int b_tarife_suresi;

// Function to check if a year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the number of days in a given month and year
int getDaysInMonth(int month, int year) {
    switch (month) {
    case 2: // February
        return isLeapYear(year) ? 29 : 28;
    case 4: case 6: case 9: case 11: // April, June, September, November
        return 30;
    default: // January, March, May, July, August, October, December
        return 31;
    }
}

// Function to validate integer input within a specific range
int getValidatedInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Geçersiz giriş. Lütfen " << min << " ile " << max << " arasında bir sayı girin." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any extra input
            return value;
        }
    }
}

// Function to calculate and display prorated charges
void hesapla(int bc, int kalan_gun) {
    int prorata = a_tarife_ucreti + b_tarife_ucreti;
    int proratab = 0;

    if (kalan_gun < 15) {
        proratab = a_tarife_ucreti + (b_tarife_ucreti * kalan_gun / 30);
    }
    else {
        proratab = (a_tarife_ucreti * kalan_gun / 30) + (b_tarife_ucreti * kalan_gun / 30);
    }

    cout << "Prorata (tam): " << prorata << " TL" << endl;
    cout << "Prorata (yarim): " << proratab << " TL" << endl;
}

int main() {
    // Get the current year for leap year calculation
    int current_year = 2024;

    // Get tariff rates for A and B
    a_tarife_ucreti = getValidatedInput("A tarifesi ücreti: ", 0, 10000);
    b_tarife_ucreti = getValidatedInput("B tarifesi ücreti: ", 0, 10000);

    // Get durations for A and B tariffs
    a_tarife_suresi = getValidatedInput("A tarifesi süresi (gün): ", 1, 365);
    b_tarife_suresi = getValidatedInput("B tarifesi süresi (gün): ", 1, 365);

    // Get billing cycle from the user
    int bc = getValidatedInput("Fatura kesim tarihi (1-4): ", 1, 4);


    int kalan_gun = 0;
    int current_day = 15; 

    switch (bc) {
    case 1:
        kalan_gun = BC1 - current_day;
        break;
    case 2:
        kalan_gun = BC2 - current_day;
        break;
    case 3: {
        int current_month = 3; 
        int days_in_month = getDaysInMonth(current_month, current_year);
        kalan_gun = days_in_month - current_day;
        break;
    }
    case 4:
        kalan_gun = BC4 - current_day;
        break;
    default:
        cout << "Geçersiz fatura kesim tarihi." << endl;
        return 1;
    }

    // Ensure remaining days are non-negative
    if (kalan_gun < 0) {
        kalan_gun += 30;
    }

   
    hesapla(bc, kalan_gun);

    return 0;
}
