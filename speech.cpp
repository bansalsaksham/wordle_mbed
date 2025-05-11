//=================================================================
// The speech class file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "speech.h"

#include "globals.h"
#include "hardware.h"

/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);

void draw_speech_bubble()
{
    uLCD.filled_rectangle(0, 92, 127, 114, BLACK);
    uLCD.rectangle(0, 92, 127, 114, GREEN);
    uLCD.filled_rectangle(1, 93,   2, 113, GREEN); // Thick border
}

void erase_speech_bubble()
{
    uLCD.filled_rectangle(2, 92, 127, 114, BLACK);
}

void draw_speech_line(const char* line, int which)
{
    uLCD.locate(1, 12 + which);
    for (int i = 0; line[i] && i < 17; i++)
    {
        uLCD.putc(line[i]);
        wait_us(30*1000);
    }
}

void speech_bubble_wait()
{
    bool waiting = true;
    Timer t;
    while(waiting)
    {
        uLCD.filled_circle(120, 120, 3, GREEN);
        t.reset(); t.start();
        while (t.read_ms() < 200)
        {
            GameInputs inputs = read_inputs();
            if (inputs.b1)
            {
                // Quit the loop
                waiting = false;
                
                // Wait for button release
                wait_us(100*1000);
                while(inputs.b1) inputs = read_inputs();
                break;
            }
        }
        t.stop();
        
        if (!waiting) break;
        
        uLCD.filled_circle(120, 120, 3, BLACK);
        t.reset(); t.start();
        while (t.read_ms() < 200)
        {
            GameInputs inputs = read_inputs();
            if (inputs.b1) 
            {
                waiting = false;
                wait_us(100*1000); 
                while(inputs.b1) inputs = read_inputs();
                break;
            }
        }
        t.stop();
    }

    uLCD.filled_circle(120, 120, 3, BLACK);
    wait_us(200*1000);
}

void speech(const char* line1, const char* line2)
{
    const char* lines[] = {line1, line2};
    long_speech(lines, 2);
}

void long_speech(const char* lines[], int n)
{
    draw_speech_bubble();
    
    int i = 0;
    do
    {
        draw_speech_line(lines[i], i%2);
        if (i%2) {
            speech_bubble_wait();
            draw_speech_bubble();
        }
    } while (++i < n);
    
    if (n%2) speech_bubble_wait();
    erase_speech_bubble();
}

