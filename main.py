#Import modules
import urllib.request, os, time

#Welcome messages
os.system("figlet -f big ESPIOT | lolcat")
os.system("figlet -f small Make better | lolcat")
print("\nConnecting to the \u001b[32mchatretriever\u001b[39m....")
print("Got answer: "+urllib.request.urlopen("https://chat-retriever.herokuapp.com").read().decode("utf-8"))
print("\nAsking server about ESP'S....")
try:
    print("ESP CID: \u001b[32m"+urllib.request.urlopen("https://chat-retriever.herokuapp.com/get/data/esp").read().decode("utf-8"))
    fss_esp_addr = urllib.request.urlopen("https://chat-retriever.herokuapp.com/get/data/esp").read().decode("utf-8")

except urllib.error.HTTPError:
    print("\u001b[31mNo ESP'S are up!\u001b[39m")

#SECOND

print("\u001b[39mAsking server about second ESP....")
try:
    print("Got answer: \u001b[32m"+urllib.request.urlopen("https://chat-retriever.herokuapp.com/get/metadata/esp").read().decode("utf-8"))
    sss_esp_addr = urllib.request.urlopen("https://chat-retriever.herokuapp.com/get/metadata/esp").read().decode("utf-8")

except urllib.error.HTTPError:
    print("\u001b[31mNo ESP'S are up!\u001b[39m")

#ASKING ESPS.......
while True:
    s_esp_addr = "https://chat-retriever.herokuapp.com/get/data/" + str(fss_esp_addr)#concat with id
    f_esp_addr = "https://chat-retriever.herokuapp.com/get/data/" + str(fss_esp_addr)#concat with id
    f_esp_sens = "https://chat-retriever.herokuapp.com/get/metadata/" + str(fss_esp_addr)#for rewriting in cycle
    s_esp_sens = "https://chat-retriever.herokuapp.com/get/metadata/" + str(sss_esp_addr)#same
    try:
        f_esp_dt = urllib.request.urlopen(f_esp_addr).read().decode("utf-8")#fetching data
        f_esp_sens = urllib.request.urlopen(f_esp_sens).read().decode("utf-8")#fetching sens
    except:f_esp_dt="unaval";f_esp_sens="unaval"
    try:
        s_esp_dt = urllib.request.urlopen(s_esp_addr).read().decode("utf-8")#fetching data
        s_esp_sens = urllib.request.urlopen(s_esp_sens).read().decode("utf-8")#fetching sens
    except:s_esp_dt="unaval";s_esp_sens="unaval"
    print("\n")
    print("\u001b[39mESP\u001b[32m"+fss_esp_addr+"\n\u001b[39msens:\u001b[35m"+f_esp_sens+"\n\u001b[39mdata: \u001b[31m"+f_esp_dt)
    print("\n")
    print("\u001b[39mESP\u001b[32m"+sss_esp_addr+"\n\u001b[39msens:\u001b[35m"+s_esp_sens+"\n\u001b[39mdata: \u001b[31m"+s_esp_dt)
    time.sleep(20)
    os.system("clear")