import { useState } from "react";
import { Text, View, Switch } from "react-native";
import styles from "../styles/styles";

export default function Main() {
  const [temperatura, setTemperatura] = useState(0);
  const [isEnabled, setIsEnabled] = useState(true);
  const toggleSwitch = () => setIsEnabled((previousState) => !previousState);

  return (
    <View style={styles.container}>
      <Text style={styles.text}>Temperatura Atual: {temperatura}</Text>
      <Text style={styles.text}>Liga / Desliga</Text>
      <Switch
        style={styles.switch}
        trackColor={{ true: "#767577", false: "#81b0ff" }}
        thumbColor={isEnabled ? "#1f1f1f" : "#11b0ff"}
        onValueChange={toggleSwitch}
        value={isEnabled}
      />
    </View>
  );
}
