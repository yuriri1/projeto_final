import { useState, useEffect } from "react";
import { Text, View, TouchableOpacity, Vibration } from "react-native";
import axios from "axios";
import styles from "../styles/styles";
import Icon from "react-native-vector-icons/FontAwesome";

export default function Main() {
  const [temperature, setTemperature] = useState(0);
  const [isEnabled, setIsEnabled] = useState(true);
  const [isToggleEnabled, setIsToggleEnabled] = useState(true);

  const toggleSwitch = () => {
    if (!isToggleEnabled) return;

    setIsToggleEnabled(false);

    setIsEnabled((previousState) => !previousState);
    Vibration.vibrate(100);

    if (isEnabled) {
      axios.put(
        "http://192.168.0.25:8090/estado",
        { state: "on" },
        { headers: { "Content-Type": "application/json" } }
      );
      console.log("Ligando");

      setTimeout(() => {
        setIsToggleEnabled(true);
        console.log("Liberando");
      }, 5000);
    } else {
      axios.put(
        "http://192.168.0.25:8090/estado",
        { state: "off" },
        { headers: { "Content-Type": "application/json" } }
      );
      console.log("Desligando");
      setTimeout(() => {
        setIsToggleEnabled(true);
        console.log("Liberando");
      }, 5000);
    }
  };

  const fetchData = async () => {
    try {
      const response = await axios.get("http://192.168.0.25:8080/temperaturas");

      setTemperature(response.data.temperature);

      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
  };

  useEffect(() => {
    const interval = setInterval(() => {
      fetchData();
    }, 50000);
    return () => clearInterval(interval);
  }, []);

  return (
    <View style={styles.container}>
      <Text style={styles.text}>Temperatura Atual: {temperature}</Text>
      <TouchableOpacity
        style={styles.button}
        onPress={toggleSwitch}
        disabled={!isToggleEnabled}
      >
        <Icon name="power-off" size={80} color={isEnabled ? "#191919" : "#f9c784"} />
      </TouchableOpacity>
    </View>
  );
}
