# 🧠 Estimador de RUL basado en clasificación Edge Impulse para NDP120

Este repositorio contiene una implementación en C++ que permite calcular la Vida Útil Restante (**RUL**, por sus siglas en inglés) de un motor brushless, utilizando las salidas categóricas de un modelo de clasificación generado en **Edge Impulse** y desplegado sobre el microcontrolador **NDP120**. El objetivo es integrar el cálculo de RUL dentro de un sistema embebido para monitorear el estado de los motores en tiempo real.

## 📌 Descripción del proyecto

Este código forma parte de una anexión técnica del trabajo de grado titulado:

> **"Dispositivo de monitoreo en motores brushless basado en TinyML"**

El modelo de clasificación fue entrenado para identificar distintos estados de salud del motor (desde sano hasta fallas progresivas) y fue exportado mediante la librería de Edge Impulse para ser ejecutado en tiempo real en la tarjeta Arduino Nicla Voice. A partir de estas etiquetas de salida, el módulo calcula una estimación del RUL de forma eficiente y adaptable al hardware.

## ⚙️ Funcionalidad

- **Historial de predicciones**: Mantiene una cola de las últimas 10 predicciones realizadas por el modelo para analizar la tendencia temporal.
- **Estado predominante**: Determina la clase más común (moda) dentro del historial.
- **Estimación de RUL**: Calcula la vida útil restante utilizando la fórmula:  
  `RUL = 100 - (score * 5)`, donde el score refleja la severidad del fallo.
- **Filtrado de categorías válidas**: Filtra predicciones no esperadas mediante una tabla definida por el usuario, asegurando solo categorías válidas.
- **Listo para microcontroladores**: Optimizado para funcionar en sistemas embebidos con recursos limitados, como el NDP120.

## 🛠 Requisitos

- Microcontrolador compatible con **NDP120** (por ejemplo: Arduino con integración Syntiant).
- Proyecto generado en **Edge Impulse** con un modelo de clasificación multiclase entrenado con datos de vibración.
- Integración con la librería `edge-impulse-sdk` exportada para NDP120.

## 🔗 Firmware oficial para Arduino Nicla Voice IMU

Para configurar y utilizar el Arduino Nicla Voice con Edge Impulse, es necesario descargar e instalar el firmware oficial proporcionado por Edge Impulse. Puedes encontrar las instrucciones detalladas y los enlaces de descarga en la documentación oficial:

👉 [Arduino Nicla Voice - Documentación de Edge Impulse](https://docs.edgeimpulse.com/docs/edge-ai-hardware/mcu-%2B-ai-accelerators/arduino-nicla-voice)

En esta página encontrarás opciones para descargar el firmware tanto para audio como para IMU, así como guías paso a paso para la instalación y configuración en diferentes sistemas operativos.

## 🧩 Integración con el Firmware de Edge Impulse

Para integrar este módulo en tu proyecto con Edge Impulse, ubica la sección del firmware donde se recibe la predicción del modelo. En el firmware oficial generado por Edge Impulse, normalmente se encuentra en el archivo `main.cpp` dentro de la función que realiza la inferencia, como por ejemplo:

```cpp
ei_impulse_result_classification result = ...;
Convierte la salida a tipo String y pásala al módulo de estimación de RUL:

cpp
Copiar
Editar
String predicted_label = String(result.classification[ix].label);
classifyAndReport(predicted_label);
Asegúrate de incluir el archivo del módulo en tu sketch o firmware, o pegar el contenido directamente si trabajas desde el Arduino IDE. Además, no olvides inicializar Serial.begin(115200); en el setup().

🧪 Recomendación
Puedes usar la función exampleUsage() incluida en el módulo para simular entradas y validar la lógica de estimación de RUL antes de integrarlo con las predicciones reales del modelo.

📁 Archivos incluidos
estimador_rul.cpp: Implementación completa del estimador de RUL con comentarios detallados para facilitar su comprensión e integración.
