# TutorialPlugin — Modificador de Velocidad MIDI

Un plugin de audio en C++ ligero construido con el **Framework JUCE** que intercepta mensajes MIDI entrantes en tiempo real y modifica la velocidad (*velocity*) de las notas `NoteOn` mediante un control deslizante (*slider*) en la interfaz gráfica.

Este proyecto fue desarrollado como un ejercicio educativo para aprender los fundamentos de la arquitectura de plugins de audio, el procesamiento MIDI en tiempo real y la comunicación entre la interfaz de usuario y el hilo de procesamiento en JUCE.

## Características

- **Procesamiento MIDI en tiempo real:** Itara sobre un `juce::MidiBuffer` para modificar la velocidad de los eventos `Note On` en el momento.
- **Interfaz gráfica personalizada:** Incluye un `juce::Slider` vertical construido con `juce::AudioProcessorEditor`.
- **Arquitectura orientada a eventos:** Utiliza `juce::Slider::Listener` para pasar de forma segura las interacciones del usuario hacia el hilo de procesamiento de audio.
- **Soporte multiformato:** Genera objetivos tanto **VST3** como **Standalone** (aplicación ejecutable independiente) para probar en DAWs (Reaper, Ableton, FL Studio, etc.) o como app autónoma.

## Tecnologías y Requisitos

- **Lenguaje:** C++17
- **Framework:** [JUCE Framework](https://juce.com/) (JUCE 8+)
- **Sistema de compilación / IDE:** Projucer / CMake / Microsoft Visual Studio (MSVC)
- **Formatos objetivo:** VST3, Aplicación Standalone

## Arquitectura y Funcionamiento

JUCE separa la lógica del plugin de audio en dos clases principales:

1. **`TutorialPluginAudioProcessor` (`PluginProcessor.h / .cpp`)**
   - Maneja el hilo de procesamiento de audio y MIDI (*audio thread*).
   - Mantiene la variable pública `noteOnVel`.
   - Sobrescribe `processBlock()`: Crea un nuevo `juce::MidiBuffer`, recorre los metadatos entrantes, actualiza el valor de velocidad para las notas que coinciden con `isNoteOn()`, y reemplaza el búfer en la cadena de audio.
2. **`TutorialPluginAudioProcessorEditor` (`PluginEditor.h / .cpp`)**
   - Gestiona la interfaz gráfica de usuario (*UI thread*).
   - Implementa `juce::Slider::Listener` para observar los cambios en la barra vertical `midiVolume`.
   - Actualiza la variable `audioProcessor.noteOnVel` dentro de la función de respuesta (*callback*) `sliderValueChanged()` cada vez que el usuario mueve el slider.

## Cómo Compilar

### Usando Projucer y Visual Studio (Windows)

1. Clona este repositorio:

   ```
   git clone https://github.com/tu-usuario/TutorialPlugin.git
   cd TutorialPlugin
   ```

2. Abre `TutorialPlugin.jucer` en **Projucer**.

3. Verifica la ruta global de los módulos de JUCE (**File > Global Paths**).

4. Haz clic en **Save Project and Open in IDE…** (Visual Studio).

5. En Visual Studio:

   - Selecciona el objetivo de compilación (`TutorialPlugin_Standalone` o `TutorialPlugin_VST3`).
   - Configura la solución en `Debug` o `Release` (`x64`).
   - Presiona `F5` para ejecutar con depurador o `Ctrl + Shift + B` para compilar.

## Aprendizajes Clave

Durante el desarrollo de este plugin, puse en práctica:

- La distinción y separación de responsabilidades entre el **Hilo de Audio** (`AudioProcessor`) y el **Hilo de Interfaz** (`AudioProcessorEditor`).
- Iteración eficiente sobre búferes MIDI en tiempo real usando bucles basados en rangos (*range-based loops*) y metadatos de C++.
- Patrones de diseño basados en observadores/escuchadores (`juce::Slider::Listener`).
- Configuración, exportación y depuración de binarios VST3 y Standalone en Visual Studio.

## Licencia

Este proyecto es de código abierto y está disponible bajo la licencia [MIT](LICENSE).