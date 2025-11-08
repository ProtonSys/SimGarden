#ifndef SETTINGS_SETTINGS_H
#define SETTINGS_SETTINGS_H

/**
 * @brief Game configuration constants using constexpr for compile-time evaluation
 */
class Settings {
public:
    class Jardim {
    public:
        static constexpr int agua_min = 80;
        static constexpr int agua_max = 100;
        static constexpr int nutrientes_min = 40;
        static constexpr int nutrientes_max = 50;
    };

    class Regador {
    public:
        static constexpr int capacidade = 200;
        static constexpr int dose = 10;
    };

    class Adubo {
    public:
        static constexpr int capacidade = 100;
        static constexpr int dose = 10;
    };

    class Jardineiro {
    public:
        static constexpr int max_movimentos = 10;
        static constexpr int max_entradas_saidas = 1;
        static constexpr int max_plantacoes = 2;
        static constexpr int max_colheitas = 5;
    };

    class Cacto {
    public:
        static constexpr int absorcao_agua_percentagem = 25;
        static constexpr int absorcao_nutrientes = 5;
        static constexpr int morre_agua_solo_maior = 100;
        static constexpr int morre_agua_solo_instantes = 3;
        static constexpr int morre_nutrientes_solo_menor = 1;
        static constexpr int morre_nutrientes_solo_instantes = 3;
        static constexpr int multiplica_nutrientes_maior = 100;
        static constexpr int multiplica_agua_maior = 50;
    };

    class Roseira {
    public:
        static constexpr int inicial_agua = 25;
        static constexpr int inicial_nutrientes = 25;
        static constexpr int perda_agua = 4;
        static constexpr int perda_nutrientes = 4;
        static constexpr int absorcao_agua = 5;
        static constexpr int absorcao_nutrientes = 8;
        static constexpr int morre_agua_menor = 1;
        static constexpr int morre_nutrientes_menor = 1;
        static constexpr int morre_nutrientes_maior = 199;
        static constexpr int multiplica_nutrientes_maior = 100;
        static constexpr int nova_nutrientes = 25;
        static constexpr int nova_agua_percentagem = 50;
        static constexpr int original_nutrientes = 100;
        static constexpr int original_agua_percentagem = 50;
    };

    class ErvaDaninha {
    public:
        static constexpr int inicial_agua = 5;
        static constexpr int inicial_nutrientes = 5;
        static constexpr int absorcao_agua = 1;
        static constexpr int absorcao_nutrientes = 1;
        static constexpr int morre_instantes = 60;
        static constexpr int multiplica_nutrientes_maior = 30;
        static constexpr int multiplica_instantes = 5;
        static constexpr int nova_nutrientes = 5;
        static constexpr int original_nutrientes = 5;
    };
};

#endif //SETTINGS_SETTINGS_H