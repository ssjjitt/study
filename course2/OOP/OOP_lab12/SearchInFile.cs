using System;
using System.Collections.Generic;
using System.IO;

public class SearchInFile
{
    private string logFilePath;

    public SearchInFile(string filePath)
    {
        logFilePath = filePath;
    }

    public void SearchByDate(DateTime startDate, DateTime endDate)
    {
        List<string> filteredEntries = FilterEntries(entry =>
        {
            string[] entryParts = entry.Split(new string[] { " - " }, StringSplitOptions.None);
            if (entryParts.Length >= 2)
            {
                DateTime entryTime;
                if (DateTime.TryParse(entryParts[0], out entryTime))
                {
                    return entryTime >= startDate && entryTime <= endDate;
                }
                else
                {
                    Console.WriteLine("Ошибка формата даты.");
                }
            }
            else
            {
                Console.WriteLine("Несоответствие количества частей разделенной записи.");
            }
            return false;
        });

        DisplayEntries(filteredEntries);
        Console.WriteLine($"Количество: {filteredEntries.Count}");
    }

    public void SearchByKeyword(string keyword)
    {
        List<string> filteredEntries = FilterEntries(entry => entry.Contains(keyword));

        DisplayEntries(filteredEntries);
        Console.WriteLine($"Количество: {filteredEntries.Count}");
    }

    public void FilterCurrentHour()
    {
        string currentHour = DateTime.Now.ToString("HH");

        List<string> filteredEntries = FilterEntries(entry =>
        {
            string[] entryParts = entry.Split(new string[] { " - " }, StringSplitOptions.None);
            if (entryParts.Length >= 2)
            {
                DateTime entryTime;
                if (DateTime.TryParse(entryParts[0], out entryTime))
                {
                    return entryTime.ToString("HH") == currentHour;
                }
                else
                {
                    Console.WriteLine("Ошибка формата даты.");
                }
            }
            else
            {
                Console.WriteLine("Несоответствие количества частей разделенной записи.");
            }
            return false;


        });

        WriteFilteredEntries(filteredEntries);
    }

    private List<string> FilterEntries(Func<string, bool> filterFunc)
    {
        List<string> logEntries = new List<string>();

        using (StreamReader reader = new StreamReader(logFilePath))
        {
            string line;
            while ((line = reader.ReadLine()) != null)
            {
                logEntries.Add(line);
            }
        }

        List<string> filteredEntries = new List<string>();

        foreach (string entry in logEntries)
        {
            if (filterFunc(entry))
            {
                filteredEntries.Add(entry);
            }
        }

        return filteredEntries;
    }

    private void DisplayEntries(List<string> entries)
    {
        Console.WriteLine("Фильтр:");
        foreach (string entry in entries)
        {
            Console.WriteLine(entry);
        }
    }

    private void WriteFilteredEntries(List<string> entries)
    {
        using (StreamWriter writer = new StreamWriter(logFilePath))
        {
            foreach (string entry in entries)
            {
                writer.WriteLine(entry);
            }
        }
    }
}