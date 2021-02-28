import pyaudio
import numpy as np
import aubio

def stream():
  CHUNK = 2**11
  RATE = 44100

  p = pyaudio.PyAudio()
  stream = p.open(format= pyaudio.paInt16, channels = 1, rate = RATE, input = True, frames_per_buffer = CHUNK)

  #initiating aubio's pitch detection object
  #pDetection = aubio.pitch("default", CHUNK, (CHUNK//2), RATE)

  while True:
    data = np.fromstring(stream.read(CHUNK), dtype=np.int16)
    data = data * np.hanning(len(data)) #smooth the FFT by windowing data
    fft = abs(np.fft.fft(data).real)
    fft = fft[:len(fft)/2] #keep only the first half
    freq = np.fft.fftfreq(CHUNK, 1.0/RATE)
    freqPeak = freq[np.where(fft==np.max(fft))[0][0]]+1
    print("peak frequency: %d Hz"%(freqPeak/10)) 
    volume = np.sum(data**2)/len(data)
    print("volume: %d"%volume)

  stream.stop_stream()
  stream.close()
  p.terminate()
  return freqPeak, volume

#correlates frequency range to a color
def sound_to_color():
  freq, vol = stream() 
  if freq < 50:
    print("green")

if __name__ == "__main__": 
  sound_to_color()


