var items = new List<string>();
items.Add("Item 1");
while (true)
{
	Console.WriteLine("\nList program");
	Console.WriteLine("1. Add item");
	Console.WriteLine("2. View items");
	Console.WriteLine("3. Remove item");
	Console.WriteLine("4. Exit");
	Console.Write("Choose an option: ");

	switch (Console.ReadLine())
	{
		case "1":
			Console.Write("Enter an item: ");
			var item = Console.ReadLine()?.Trim();


			if (!string.IsNullOrWhiteSpace(item))
			{
				items.Add(item);
				Console.WriteLine("Item added.");
			}
			else
			{
				Console.WriteLine("Item cannot be empty.");
			}

			break;

		case "2":
			if (items.Count == 0)
			{
				Console.WriteLine("The list is empty.");
				break;
			}

			Console.WriteLine("\nItems:");
			for (var index = 0; index < items.Count; index++)
			{
				Console.WriteLine($"{index + 1}. {items[index]}");
			}

			break;

		case "3":
			if (items.Count == 0)
			{
				Console.WriteLine("The list is empty.");
				break;
			}

			Console.Write("Enter the item number to remove: ");
			if (int.TryParse(Console.ReadLine(), out var itemNumber) &&
				itemNumber >= 1 && itemNumber <= items.Count)
			{
				var removedItem = items[itemNumber - 1];
				items.RemoveAt(itemNumber - 1);
				Console.WriteLine($"Removed: {removedItem}");
			}
			else
			{
				Console.WriteLine("Please enter a valid item number.");
			}

			break;

		case "4":
			Console.WriteLine("Goodbye!");
			return;

		default:
			Console.WriteLine("Please choose an option from 1 to 4.");
			break;
	}
}

