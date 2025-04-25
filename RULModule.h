// -----------------------------------------------------------------------------
// Código auxiliar para estimación de RUL (Remaining Useful Life)
// Autor: [Tu nombre o iniciales si deseas]
// Trabajo de grado: Dispositivo de monitoreo en motores brushless basado en TinyML
// Plataforma embebida: Arduino + NDP120 (Edge Impulse)
// Este código es compatible con el modelo generado por Edge Impulse para el NDP120
// -----------------------------------------------------------------------------
// Funcionalidad:
// - Almacena las últimas predicciones generadas por el modelo (categorías).
// - Determina la categoría predominante mediante la moda estadística.
// - Calcula el RUL asociado según una tabla de puntuaciones asignadas por clase.
// -----------------------------------------------------------------------------

#define HISTORY_SIZE 10  // Tamaño del historial de predicciones a conservar

// Librerías estándar de C++ utilizadas
#include <vector>        // Para manejar el historial como vector dinámico
#include <map>           // Para asociar categorías a puntuaciones (scores)
#include <Arduino.h>     // Incluida para compatibilidad con entornos Arduino

// Vector para almacenar el historial de predicciones recientes
std::vector<String> predictionHistory;

// Tabla que asocia cada categoría a una puntuación de desgaste (score)
// Esta tabla es definida manualmente según criterios del análisis de fallas
std::map<String, int> categoryScores = {
    {"Hpf1", 5},
    {"Hpf2", 10},
    {"Hpf3", 15},
    {"Hpf4", 20},
    {"Hpf5", 25},
    {"Hpf6", 30},
    {"Hpf7", 35},
    {"Hpf8", 40},
    {"Hpf9", 45},
    {"Hpf10", 50},
    {"Hpf10bf1", 60},
    {"Hpf10bf2", 70},
    {"Hpf10bf3", 80},
    {"Hpf10bf4", 90},
    {"Hpf10bf5", 100},
    {"Hbf1", 60},
    {"Hbf2", 70},
    {"Hbf3", 80},
    {"Hbf4", 90},
    {"Hbf5", 100},
    {"H", 0},
    {"Hn", 0}
};

// -----------------------------------------------------------------------------
// Función: updateHistory
// Descripción: Actualiza el vector de historial con una nueva predicción.
// Si se alcanza el tamaño máximo definido, elimina la predicción más antigua.
// -----------------------------------------------------------------------------
void updateHistory(String category) {
    if (predictionHistory.size() >= HISTORY_SIZE) {
        predictionHistory.erase(predictionHistory.begin());  // elimina el más antiguo
    }
    predictionHistory.push_back(category);  // añade el nuevo
}

// -----------------------------------------------------------------------------
// Función: calculateMode
// Descripción: Calcula la categoría más frecuente (moda) en el historial.
// Esta categoría es interpretada como el estado predominante del motor.
// -----------------------------------------------------------------------------
String calculateMode() {
    std::map<String, int> freq;

    for (const auto &cat : predictionHistory) {
        freq[cat]++;
    }

    String mode = "";
    int maxCount = 0;
    for (const auto &entry : freq) {
        if (entry.second > maxCount) {
            maxCount = entry.second;
            mode = entry.first;
        }
    }
    return mode;
}

// -----------------------------------------------------------------------------
// Función: calculateRUL
// Descripción: Calcula el valor estimado de vida útil restante (RUL) a partir
// de la categoría predominante. Se usa una fórmula lineal basada en score.
// RUL = 100 - (score * 5)
// -----------------------------------------------------------------------------
int calculateRUL(String category) {
    int score = categoryScores[category];
    return 100 - (score * 5);
}

// -----------------------------------------------------------------------------
// Función: classifyAndReport
// Descripción: Ejecuta todo el flujo de lógica: registra una predicción,
// calcula la categoría más frecuente y estima el RUL. Imprime los resultados.
// -----------------------------------------------------------------------------
void classifyAndReport(String category) {
    Serial.print("Categoría detectada: ");
    Serial.println(category);

    updateHistory(category);  // Actualiza historial
    String modeCategory = calculateMode();  // Determina categoría predominante

    Serial.print("Categoría predominante: ");
    Serial.println(modeCategory);

    int rul = calculateRUL(modeCategory);  // Calcula RUL
    Serial.print("Vida Útil Restante (RUL): ");
    Serial.println(rul);
}

// -----------------------------------------------------------------------------
// Función: exampleUsage
// Descripción: Simula el funcionamiento del sistema con ejemplos de predicción.
// Ideal para pruebas antes de integrar con modelo real de Edge Impulse.
// -----------------------------------------------------------------------------
void exampleUsage() {
    classifyAndReport("Hpf10");
    classifyAndReport("Hpf10bf2");
    classifyAndReport("Hbf3");
}
