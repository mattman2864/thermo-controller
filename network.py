import network
station = network.WLAN(network.STA_IF)
station.active(True)
station.connect('PARI_Office', 'PARI*13598')
station.isconnected()