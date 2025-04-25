// -----------------------------------------------------------------------------
// Módulo único para estimación de RUL basado en clasificación
// Autor: [Andersson Bastidas Morillo]
// Proyecto: Dispositivo de monitoreo en motores brushless basado en TinyML
// -----------------------------------------------------------------------------

#pragma once
#include <Arduino.h>
#include <vector>
#include <map>

#define HISTORY_SIZE 10  // Número de predicciones recientes a considerar

// Historial circular de categorías predichas
std::vector<String> predictionHistory;

// Tabla de puntuaciones asignadas por clase (filtradas según modelo)
std::map<String, int> categoryScores = {
    {"Hpf1", 5},
    {"Hpf5", 25},
    {"Hpf9", 45},
    {"Hpf10", 50},
    {"Hbf1", 60},
    {"Hbf3", 80},
    {"Hp", 0},
    {"Hpn", 0},
    {"Hpbf1", 60},
    {"Hpbf3", 80}
};

// Verifica si la categoría es válida según el mapa definido
bool isValidCategory(const String& category) {
    return categoryScores.find(category) != categoryScores.end();
}

// Actualiza el historial con una nueva predicción
void updateHistory(const String& category) {
    if (predictionHistory.size() >= HISTORY_SIZE) {
        predictionHistory.erase(predictionHistory.begin());
    }
    predictionHistory.push_back(category);
}

// Calcula la moda del historial
String calculateMode() {
    std::map<String, int> freq;
    for (const auto& cat : predictionHistory) {
        freq[cat]++;
    }

    String mode = "";
    int maxCount = 0;
    for (const auto& entry : freq) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            mode = entry.first;
        }
    }
    return mode;
}

// Calcula el RUL: 100 - (score * 5)
int calculateRUL(const String& category) {
    int score = categoryScores[category];
    return 100 - (score * 5);
}

// Función principal que ejecuta la lógica completa
void classifyAndReport(const String& category) {
    Serial.println("--------------------------------------------------");

    if (!isValidCategory(category)) {
        Serial.print("⚠️  Categoría inválida recibida: ");
        Serial.println(category);
        return;
    }

    Serial.print("✅ Categoría detectada: ");
    Serial.println(category);

    updateHistory(category);

    String modeCategory = calculateMode();
    Serial.print("📊 Categoría predominante: ");
    Serial.println(modeCategory);

    int rul = calculateRUL(modeCategory);
    Serial.print("🔧 Vida Útil Restante (RUL): ");
    Serial.print(rul);
    Serial.println("%");
}

// Ejemplo de uso manual
void exampleUsage() {
    classifyAndReport("Hpf10");
    classifyAndReport("Hpbf3");
    classifyAndReport("Hbf3");
    classifyAndReport("INVALIDA");  // No será procesada
}
