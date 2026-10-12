/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TutorialPluginAudioProcessorEditor::TutorialPluginAudioProcessorEditor (TutorialPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);

    // Métodos que definen los parámetros del objeto slider
    midiVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    midiVolume.setRange(0.0, 127.0, 1.0);
    midiVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    midiVolume.setPopupDisplayEnabled(true, false, this);
    midiVolume.setTextValueSuffix("Volumen");
    midiVolume.setValue(1.0);

    // Función que agrega el slider al editor y lo hace visible
    addAndMakeVisible(&midiVolume);

    midiVolume.addListener(this);

}

TutorialPluginAudioProcessorEditor::~TutorialPluginAudioProcessorEditor()
{
}

//==============================================================================
void TutorialPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Rellena toda la ventana de blanco
    g.fillAll(juce::Colours::white);

    // Establece el color del dibujo/texto en negro
    g.setColour(juce::Colours::black);

    // Define el tamaño de la fuente y dibuja el texto centrado arriba
    g.setFont(juce::FontOptions(15.0f));
    g.drawFittedText("Volumen Midi", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void TutorialPluginAudioProcessorEditor::resized()
{
    // Define la posición y el tamaño del slider con los argumentos (x, y, ancho, alto)
    midiVolume.setBounds(40, 30, 20, getHeight() - 60);

}

void TutorialPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    audioProcessor.noteOnVel = midiVolume.getValue();
}
