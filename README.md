# 🧠 Estimador de RUL basado en clasificación Edge Impulse para NDP120

Este repositorio contiene una implementación en C++ que permite calcular la Vida Útil Restante (**RUL**, por sus siglas en inglés) de un motor brushless, utilizando las salidas categóricas de un modelo de clasificación generado en **Edge Impulse** y desplegado sobre el microcontrolador **NDP120**.

## 📌 Descripción del proyecto

Este código forma parte de una anexión técnica del trabajo de grado titulado:

> **"Dispositivo de monitoreo en motores brushless basado en TinyML"**

El modelo de clasificación fue entrenado para identificar distintos estados de salud del motor (desde sano hasta fallas progresivas) y fue exportado mediante la librería de Edge Impulse para ser ejecutado en tiempo real. A partir de estas etiquetas de salida, el presente módulo calcula una estimación del RUL de forma eficiente y adaptable al hardware.

## ⚙️ Funcionalidad

- **Historial de predicciones**: Mantiene una cola de predicciones recientes para analizar la tendencia temporal.
- **Estado predominante**: Determina la clase más común (moda) dentro del buffer.
- **Estimación de RUL**: Convierte la clase predominante en una puntuación de desgaste y estima la vida útil restante mediante una fórmula ajustable.
- **Listo para microcontroladores**: Optimizado para funcionar dentro de sistemas embebidos con recursos limitados.

## 🛠 Requisitos

- Microcontrolador compatible con **NDP120** (por ejemplo: Arduino con integración Syntiant).
- Proyecto generado en **Edge Impulse** con modelo de clasificación multiclase.
- Integración con la librería `edge-impulse-sdk` exportada para NDP120.

## 🔗 Firmware oficial para Arduino Nicla Voice IMU

Para configurar y utilizar el Arduino Nicla Voice con Edge Impulse, es necesario descargar e instalar el firmware oficial proporcionado por Edge Impulse. Puedes encontrar las instrucciones detalladas y los enlaces de descarga en la documentación oficial:

👉 [Arduino Nicla Voice - Documentación de Edge Impulse](https://docs.edgeimpulse.com/docs/edge-ai-hardware/mcu-%2B-ai-accelerators/arduino-nicla-voice)

En esta página encontrarás opciones para descargar el firmware tanto para audio como para IMU, así como guías paso a paso para la instalación y configuración en diferentes sistemas operativos.

## 🧪 Uso

Integra este archivo `.cpp` dentro del flujo de inferencia del microcontrolador, justo después de obtener la etiqueta de predicción del modelo. La función principal calculará el estado predominante y el RUL estimado, los cuales pueden ser usados para alertas, registros o visualización.

## 📁 Archivos incluidos

- `estimador_rul.cpp`: Contiene la implementación completa del estimador.
- Comentarios exhaustivos para facilitar la comprensión e integración.

## 🌐 English Version

### 🧠 RUL Estimator Based on Edge Impulse Classification for NDP120

This repository includes a C++ implementation for computing the **Remaining Useful Life (RUL)** of a brushless motor using categorical outputs from a classification model generated in **Edge Impulse** and deployed on the **NDP120** microcontroller.

### 📌 Project Description

This code is part of a technical annex of the undergraduate thesis titled:

> **"Monitoring Device for Brushless Motors Based on TinyML"**

The classification model was trained to recognize different health states of the motor (from healthy to progressively failing) and exported through the Edge Impulse library for real-time execution. This module interprets those output labels to estimate the RUL effectively and efficiently.

### ⚙️ Features

- **Prediction history**: Maintains a recent prediction queue to assess temporal trends.
- **Predominant state**: Calculates the most frequent class (mode) from the buffer.
- **RUL estimation**: Converts the predominant class into a degradation score and computes remaining life using a linear formula.
- **Microcontroller ready**: Designed for constrained environments in embedded systems.

### 🛠 Requirements

- Microcontroller with **NDP120** (e.g., Arduino with Syntiant integration).
- Trained **Edge Impulse** project with a multi-class classification model.
- Integration with the exported `edge-impulse-sdk` for NDP120.

### 🔗 Official Firmware for Arduino Nicla Voice IMU

To set up and use the Arduino Nicla Voice with Edge Impulse, you need to download and install the official firmware provided by Edge Impulse. Detailed instructions and download links are available in the official documentation:

👉 [Arduino Nicla Voice - Edge Impulse Documentation](https://docs.edgeimpulse.com/docs/edge-ai-hardware/mcu-%2B-ai-accelerators/arduino-nicla-voice)

This page provides options to download firmware for both audio and IMU, along with step-by-step guides for installation and configuration on various operating systems.

### 🧪 Usage

Integrate this `.cpp` file into the inference loop of your firmware, right after the model prediction. The main function will compute the predominant state and RUL, which can be used for triggering alarms, logging, or display.

### 📁 Included Files

- `estimador_rul.cpp`: Full implementation of the RUL estimator.
- Fully commented to ease integration and understanding.
