using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public static class SaveSystem 
{
    public static void SavePlayer(PlayerMovement player, BackpackManager back)
    {
        BinaryFormatter formatter = new BinaryFormatter();
        string path = Application.persistentDataPath + "/player.Save";
        FileStream stream = new FileStream(path, FileMode.Create);

        PlayerData data = new PlayerData(player, back);

        formatter.Serialize(stream, data);
        stream.Close();
        /*        PlayerData data = new PlayerData(player, back);
                PlayerPrefs.SetString("jsondata", JsonUtility.ToJson(data));*/
    }

    public static PlayerData LoadPlayer()
    {
        string path = Application.persistentDataPath + "/player.Save";
        if (File.Exists(path))
        {
            BinaryFormatter formatter = new BinaryFormatter();
            FileStream stream = new FileStream(path, FileMode.Open);

            PlayerData data = formatter.Deserialize(stream) as PlayerData;
            stream.Close();

            return data;
        }
        else
        {
            return null;
        }
/*
        PlayerData data = JsonUtility.FromJson<PlayerData>(PlayerPrefs.GetString("jsondata"));
        return data;*/
    }
}
