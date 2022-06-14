#include <iostream>
#include <string>
 
using namespace std;

class Country {
    public:
        bool operator < (Country const country) {
            if (this->goldMedals < country.goldMedals) return true;
            else if (this->goldMedals > country.goldMedals) return false;

            if (this->silverMedals < country.silverMedals) return true;
            else if (this->silverMedals > country.silverMedals) return false;

            if (this->bronzeMedals < country.bronzeMedals) return true;
            else if (this->bronzeMedals > country.bronzeMedals) return false;

            return false;
        }

        bool operator > (Country const country) {
            if (this->goldMedals > country.goldMedals) return true;
            else if (this->goldMedals < country.goldMedals) return false;

            if (this->silverMedals > country.silverMedals) return true;
            else if (this->silverMedals < country.silverMedals) return false;

            if (this->bronzeMedals > country.bronzeMedals) return true;
            else if (this->bronzeMedals < country.bronzeMedals) return false;

            return false;
        }

        bool operator == (Country const country) {
            if (this->goldMedals != country.goldMedals) return false;
            if (this->silverMedals != country.silverMedals) return false;
            if (this->bronzeMedals != country.bronzeMedals) return false;
            
            return true;
        }

        std::string getName() {
            return this->name;
        }

    private:
        std::string name;
        int goldMedals;
        int silverMedals;
        int bronzeMedals;

    friend class OlimpicCountries;
};

class OlimpicCountries {
    public:
        OlimpicCountries() {
            this->countriesAmount = -1;
            countries = nullptr;
        }

        OlimpicCountries(int countriesAmount) {
            this->countriesAmount = countriesAmount;
            countries = new Country[countriesAmount];
        }

    private:
        int countriesAmount;
        Country *countries;
};

int main() {
 
    /**
     * Escreva a sua solução aqui
     * Code your solution here
     * Escriba su solución aquí
     */
 
    return 0;
}