import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';
 
class _FavoritesDemo extends StatefulWidget {
  const _FavoritesDemo();

  @override
  State<_FavoritesDemo> createState() => _FavoritesDemoState();
}

class _FavoritesDemoState extends State<_FavoritesDemo> {
  final _items = const ['Hotel A', 'Hotel B'];
  final Set<String> _favorites = {};

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Favorites')),
      body: ListView(
        children: _items.map((title) {
          final isFav = _favorites.contains(title);
          return ListTile(
            title: Text(title),
            trailing: IconButton(
              key: Key('fav_$title'),
              icon: Icon(isFav ? Icons.favorite : Icons.favorite_border),
              onPressed: () => setState(() {
                if (isFav) {
                  _favorites.remove(title);
                } else {
                  _favorites.add(title);
                }
              }),
            ),
          );
        }).toList(),
      ),
    );
  }
}

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  testWidgets('Integration 2/3 (User): toggle favorite (tap + expect)', (tester) async {
    await tester.pumpWidget(const MaterialApp(home: _FavoritesDemo()));

    await tester.tap(find.byKey(const Key('fav_Hotel A')));
    await tester.pump();

    final icon = tester.widget<IconButton>(find.byKey(const Key('fav_Hotel A'))).icon as Icon;
    expect(icon.icon, Icons.favorite);
  });
}

