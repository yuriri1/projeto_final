import { StyleSheet } from "react-native";

const styles = StyleSheet.create({
  container: {
    flex: 1,
    dispplay: "flex",
    alignItems: "center",
    justifyContent: "center",
    backgroundColor: "#191919",
  },
  text: {
    fontSize: 20,
    fontWeight: "bold",
    marginBottom: 20,
    color: "#fff",
  },
  button: {
    alignItems: "center",
    backgroundColor: "#e7e7e7",
    padding: 10,
    width: 100,
    height: 100,
    borderRadius: 100,
    borderWidth: 2,
    borderColor: "#5b5b5b",
  }
});

export default styles;
