import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';

class _AdminAddHotelDemo extends StatefulWidget {
  const _AdminAddHotelDemo();

  @override
  State<_AdminAddHotelDemo> createState() => _AdminAddHotelDemoState();
}

class _AdminAddHotelDemoState extends State<_AdminAddHotelDemo> {
  final _controller = TextEditingController();
  final List<String> _hotels = [];

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Admin Panel')),
      body: Column(
        children: [
          TextField(
            key: const Key('titleField'),
            controller: _controller,
            decoration: const InputDecoration(labelText: 'Title'),
          ),
          ElevatedButton(
            key: const Key('addHotelBtn'),
            onPressed: () {
              setState(() => _hotels.add(_controller.text));
              ScaffoldMessenger.of(context).showSnackBar(
                const SnackBar(content: Text('Hotel added')),
              );
            },
            child: const Text('Add'),
          ),
          Expanded(
            child: ListView(
              children: _hotels.map((t) => ListTile(title: Text(t))).toList(),
            ),
          ),
        ],
      ),
    );
  }
}

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  testWidgets('Integration 1/3 (Admin): add hotel flow (enterText + tap + expect)', (tester) async {
    await tester.pumpWidget(const MaterialApp(home: _AdminAddHotelDemo()));

    await tester.enterText(find.byKey(const Key('titleField')), 'Integration Hotel');
    await tester.tap(find.byKey(const Key('addHotelBtn')));
    await tester.pump();

    expect(find.text('Hotel added'), findsOneWidget);
    expect(find.widgetWithText(ListTile, 'Integration Hotel'), findsOneWidget);
  });
}

