import { StyleSheet } from "react-native";

const styles = StyleSheet.create({
  container: {
    flex: 1,
    dispplay: "flex",
    alignItems: "center",
    justifyContent: "center",
  },
  text: {
    fontSize: 20,
    fontWeight: "bold",
    marginBottom: 20,
  },
  switch: {
    transform: [{ scaleX: 2 }, { scaleY: 2 }],
  },
});

export default styles;
