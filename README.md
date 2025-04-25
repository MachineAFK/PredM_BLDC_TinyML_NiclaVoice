
# 🧠 Integración de Modelo Edge Impulse con Arduino Nicla Voice para Estimación de RUL

Esta guía describe cómo integrar un modelo de aprendizaje automático entrenado en **Edge Impulse** en la tarjeta **Arduino Nicla Voice**, que incorpora el chip **Syntiant NDP120**, para implementar un sistema de estimación de **Vida Útil Restante (RUL)** en motores brushless DC (BLDC).

---

## 📦 Contenido del Proyecto

- Modelo TinyML exportado en formato `.synpkg` con su carpeta con varibales y metadatos correspondientes al modelo.
- [Firmware original desde Edge Impulse para Nicla Voice](https://github.com/edgeimpulse/firmware-arduino-nicla-voice).
- codigo `ei_syntiant_ndp120.cpp` del anterior firmware modificado para reemplazar asi como tambien la metadata y las variables del modelo.
- Módulo personalizado para inferencia y cálculo de RUL (`RULModule.h`).

---

## 🧰 Requisitos

- [Arduino IDE](https://www.arduino.cc/en/software)
- Tarjeta **Arduino Nicla Voice**
- Cuenta en [Edge Impulse](https://www.edgeimpulse.com)
- Modelo entrenado y exportado como `.synpkg`

---

## 📤 Exportación del Modelo desde Edge Impulse

1. Entrena tu modelo en Edge Impulse con datos relevantes del motor (por ejemplo, vibracion o audio).
2. Dirígete a la pestaña **Deployment** de tu proyecto.
3. Selecciona **Syntiant NDP120 library (.synpkg)** y descarga el archivo.
---

## 🔌 Integración del Modelo en el Firmware
1. Extrae la libreria firmware-arduino-nicla-voice y reemplaza en la ruta firmware-arduino-nicla-voice/src/model-parameters 
2. Reemplaza la carpeta model_metadata de `predm_largeimu-syntiant-ndp120-lib-tdk-v13.zip` en el firmware original y haz el build correspondiente, en este caso con IMU.
Tambien se incluye un binario generado en edgeimpulse que facilita la subida a la tarjeta aunque sin el modulo.
3. Copia el archivo `ei_model.synpkg` que esta en `predm_largeimu-syntiant-ndp120-lib-tdk-v13.zip` en este repositorio y reemplazalo en la carpeta`ndp120/` del firmware base y [flashealo](https://docs.arduino.cc/tutorials/nicla-voice/user-manual/) en el NDP con los algoritmos que proporcionan en el manual de arduino.
---

🔧 Compilación del Código Fuente
Una vez que hayas añadido tu propia lógica, deberás compilar y cargar el firmware en tu dispositivo. A continuación, se detallan los pasos necesarios para cada sistema operativo:

Windows
Ejecuta el siguiente script para actualizar las librerías (solo si estás utilizando Syntiant TinyML):
update_libraries_windows.bat

Para compilar el firmware con soporte de audio:
arduino-win-build.bat --build

Si también necesitas soporte para IMU, añade el siguiente flag:
arduino-win-build.bat --build --with-imu

Para cargar (flashear) el firmware en la placa:
arduino-win-build.bat --flash

Linux y macOS
Para compilar el firmware con soporte de audio:
./arduino-build.sh --build

Si también necesitas soporte para IMU, añade el siguiente flag:
./arduino-build.sh --build --with-imu

Para cargar (flashear) el firmware en la placa:
./arduino-build.sh --flash

🚀 Despliegue de tu Impulse
Una vez compilado el firmware de Arduino, deberás reemplazar los archivos correspondientes en el firmware base con los generados por tu proyecto.

En Arduino Nicla Voice
Toma el archivo .elf generado por Arduino y renómbralo a:
firmware.ino.elf

Reemplaza el archivo firmware.ino.elf del firmware por defecto con el nuevo generado.
(El firmware por defecto puede descargarse desde la documentación oficial).

Sustituye el archivo ei_model.synpkg del firmware por defecto por el modelo generado desde la librería de Syntiant.

Ejecuta el script correspondiente a tu sistema operativo para flashear la placa.




---

## 🔎 Estimación de RUL (`RULModule.h`)

El archivo `RULModule.h` implementa una lógica personalizada que interpreta las predicciones del modelo para calcular la vida útil restante del motor.

### ¿Cómo funciona?

- El modelo predice una clase basada en el audio captado.
- Se valida que la clase esté definida en el sistema.
- Se mantiene un historial circular de predicciones recientes.
- Se calcula la clase más frecuente (moda).
- A cada clase se le asigna una puntuación predefinida.
- El RUL se calcula con la fórmula:
  RUL = 100 - (puntuación * 5)


- El resultado se muestra en el monitor serial.

---

## 👨‍💻 Guía de Uso

1. Conecta la Nicla Voice vía USB.
2. Carga el firmware desde el Arduino IDE.
3. Abre el monitor serial para observar las predicciones en tiempo real.
4. Interpreta el valor de RUL para tomar decisiones de mantenimiento predictivo.

> ⚠️ Un RUL bajo o negativo puede indicar un estado de desgaste crítico o una clase fuera del rango esperado.

---

## 🧠 Aplicaciones

- Monitoreo inteligente de motores BLDC.
- Detección temprana de fallas mediante análisis de señales.
- Sistemas embebidos de bajo consumo con capacidades de aprendizaje automático.

---

## 📚 Recursos Útiles

- [📖 Edge Impulse para Syntiant NDP120](https://docs.edgeimpulse.com/docs/run-inference/cpp-library/on-your-syntiant-tinyml-board)
- [🔍 Tutorial: Reconocimiento de Movimiento con Syntiant](https://docs.edgeimpulse.com/docs/run-inference/hardware-specific-tutorials/motion-recognition-syntiant)


---

## 📊 Dataset de Vibración de Motor BLDC

Este repositorio incluye un **dataset original de vibración** capturado desde un **motor BLDC** utilizando la tarjeta **Arduino Nicla Voice**. Los datos fueron adquiridos a través del puerto serial mediante una interfaz desarrollada en **MATLAB**.

### 📌 Descripción

- El dataset contiene señales de vibración registradas bajo **diferentes condiciones progresivas** del mismo motor a lo largo del tiempo.
- Las condiciones reflejan el desgaste o cambios operativos simulados o reales del motor.
- Los datos fueron obtenidos usando el **acelerómetro integrado** en la Nicla Voice.
- El formato del dataset es apto para ser utilizado en tareas de entrenamiento, validación o análisis exploratorio.
- 🔢 **Para este proyecto en particular, se utilizaron los primeros 50 registros de cada categoría**, aunque algunas clases cuentan con una cantidad significativamente mayor de muestras en el dataset completo.

### 🧪 Aplicación y Valor Investigativo

- Ideal para estudios en **mantenimiento predictivo**, **diagnóstico de fallas** y **aprendizaje automático** aplicado al análisis de vibraciones.
- Puede utilizarse para construir modelos de predicción de estado o estimación de vida útil (RUL) en sistemas rotativos.
- Proporciona una base de datos valiosa y realista para pruebas y validaciones académicas o de desarrollo.

### 📂 Disponibilidad

- El dataset está disponible en este repositorio bajo una licencia **abierta** para su uso libre con fines investigativos, educativos o de desarrollo.
