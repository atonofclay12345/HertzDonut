import pyaudio
import numpy as np

CHUNK = 2**11
RATE = 44100

p = pyaudio.PyAudio()
stream = p.open(format= pyaudio.paInt16, channels = 1, rate = RATE, input = True, frames_per_buffer = CHUNK)


for i in range(int(10*44100/1024)):
  data = np.fromstring(stream.read(CHUNK), dtype=np.int16)
  data = data * np.hanning(len(data)) #smooth the FFT by windowing data
  fft = abs(np.fft.fft(data).real)
  fft = fft[:len(fft)/2] #keep only the first half
  freq = np.fft.fftfreq(CHUNK, 1.0/RATE)
  freqPeak = freq[np.where(fft==np.max(fft))[0][0]]+1
  print("peak frequency: %d Hz"%freqPeak)
  #eak = np.average(np.abs(data))*2
  #bars = "#"*int(50*peak/2**16)
  #print("%04d %05d %s"%(i,peak,bars))

stream.stop_stream()
stream.close()
p.terminate()

#import sounddevice as sd

#for i in range(30): #30 updates in 1 second
  #rec = sd.rec(44100/30)
  #sounddevice.wait()
  #print(rec.shape)


