#include <Arduino.h>
#include <samplerate.h>
#include <math.h>

#define INPUT_SAMPLE_RATE 44100
#define OUTPUT_SAMPLE_RATE 48000
#define INPUT_FRAMES 4410  // 0.1 seconds of audio at 44.1 kHz
#define OUTPUT_FRAMES (INPUT_FRAMES * OUTPUT_SAMPLE_RATE / INPUT_SAMPLE_RATE)

float input[INPUT_FRAMES];
float output[OUTPUT_FRAMES];

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }
    Serial.println("Starting libsamplerate timing test");

    // Fill input array with sample data (e.g., a sine wave)
    for (int i = 0; i < INPUT_FRAMES; i++) {
        input[i] = sin(2 * PI * i / INPUT_FRAMES);
    }

    // Set up SRC_DATA structure
    SRC_DATA src_data;
    src_data.data_in = input;
    src_data.data_out = output;
    src_data.input_frames = INPUT_FRAMES;
    src_data.output_frames = OUTPUT_FRAMES;
    src_data.src_ratio = (double)OUTPUT_SAMPLE_RATE / INPUT_SAMPLE_RATE;
    src_data.end_of_input = 0;

    // Set converter type to SINC_FASTEST
    int converter_type = SRC_SINC_FASTEST; // Using fastest sinc converter
    Serial.print("Using converter type: ");
    Serial.println(converter_type);

    // Measure the time taken for the conversion
    unsigned long start_time = millis();
    int error = src_simple(&src_data, converter_type, 1); // Using fastest sinc converter
    unsigned long end_time = millis();

    if (error) {
        Serial.print("Error: ");
        Serial.println(src_strerror(error));
    } else {
        Serial.print("Resampling successful. Time taken: ");
        Serial.print(end_time - start_time);
        Serial.println(" ms");
        Serial.print("Input frames used: ");
        Serial.println(src_data.input_frames_used);
        Serial.print("Output frames generated: ");
        Serial.println(src_data.output_frames_gen);
    }
}

void loop() {
    // put your main code here, to run repeatedly:
}